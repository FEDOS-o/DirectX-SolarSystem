#pragma once
#include "GameComponent.h"
#include "Camera.h"
#include "OrbitalCameraGameComponent.h"
#include "FirstPersonCameraGameComponent.h"
#include <SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class InfiniteGridGameComponent : public GameComponent {
private:
    struct Vertex {
        Vector3 position;
        Vector4 color;
    };

    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11InputLayout* inputLayout;
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
    ID3D11Buffer* constantBuffer;

    float spacing;
    float baseFadeDistance;
    int currentGridSize;
    UINT indexCount;
    bool initialized;

public:
    InfiniteGridGameComponent(Game* game, float spacing = 1.0f, float baseFadeDistance = 20.0f)
        : GameComponent(game)
        , spacing(spacing)
        , baseFadeDistance(baseFadeDistance)
        , currentGridSize(200)
        , vertexBuffer(nullptr)
        , indexBuffer(nullptr)
        , inputLayout(nullptr)
        , vertexShader(nullptr)
        , pixelShader(nullptr)
        , constantBuffer(nullptr)
        , indexCount(0)
        , initialized(false)
    {
    }

    void Initialize() override {
        if (initialized) return;

        CreateGridGeometry();
        CreateShaders();
        CreateConstantBuffer();

        initialized = true;
    }

    void Update(float deltaTime) override {
        if (!game || !game->Camera) return;

        int newGridSize = 200;

        OrbitalCameraGameComponent* orbitalCam = dynamic_cast<OrbitalCameraGameComponent*>(game->Camera);
        if (orbitalCam) {
            float distToTarget = (orbitalCam->GetPosition() - Vector3(0, 0, 0)).Length();
            newGridSize = 200 + (int)(distToTarget * 3.0f);
            if (newGridSize > 800) newGridSize = 800;
        }
        else {
            float height = game->Camera->GetPosition().y;
            if (height > 10.0f) {
                newGridSize = 200 + (int)(height * 2.0f);
                if (newGridSize > 400) newGridSize = 400;
            }
        }

        if (newGridSize != currentGridSize) {
            currentGridSize = newGridSize;
            RebuildGrid(currentGridSize);
        }
    }

    void Draw() override {
        if (!initialized || !game || !game->Context || !game->Camera || !vertexBuffer) {
            return;
        }

        Vector3 cameraPos = game->Camera->GetPosition();
        float currentFade = baseFadeDistance;
        OrbitalCameraGameComponent* orbitalCam = dynamic_cast<OrbitalCameraGameComponent*>(game->Camera);
        if (orbitalCam) {
            float distToTarget = (orbitalCam->GetPosition() - Vector3(0, 0, 0)).Length();
            currentFade = baseFadeDistance + distToTarget * 2.0f;
            if (currentFade > 1000.0f) currentFade = 1000.0f;
        }
        else {
            float height = cameraPos.y;
            if (height > 10.0f) {
                currentFade = baseFadeDistance + height * 2.0f;
                if (currentFade > 500.0f) currentFade = 500.0f;
            }
        }

        float offsetX = fmodf(cameraPos.x, spacing);
        float offsetZ = fmodf(cameraPos.z, spacing);

        Matrix translation = Matrix::CreateTranslation(-offsetX, 0, -offsetZ);
        Matrix wvp = translation * game->Camera->GetViewMatrix() * game->Camera->GetProjectionMatrix();

        struct ConstantBufferData {
            Matrix worldViewProj;
            Vector3 cameraPosition;
            float fadeDistance;
            float spacing;
            Vector3 padding1;
        };

        ConstantBufferData cb;
        cb.worldViewProj = wvp.Transpose();
        cb.cameraPosition = cameraPos;
        cb.fadeDistance = currentFade;
        cb.spacing = spacing;
        cb.padding1 = Vector3(0, 0, 0);

        game->Context->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        game->Context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        game->Context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        game->Context->IASetInputLayout(inputLayout);
        game->Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        game->Context->VSSetShader(vertexShader, nullptr, 0);
        game->Context->VSSetConstantBuffers(0, 1, &constantBuffer);
        game->Context->PSSetShader(pixelShader, nullptr, 0);

        game->Context->DrawIndexed(indexCount, 0, 0);
    }

    void DestroyResources() override {
        if (vertexBuffer) { vertexBuffer->Release(); vertexBuffer = nullptr; }
        if (indexBuffer) { indexBuffer->Release(); indexBuffer = nullptr; }
        if (inputLayout) { inputLayout->Release(); inputLayout = nullptr; }
        if (vertexShader) { vertexShader->Release(); vertexShader = nullptr; }
        if (pixelShader) { pixelShader->Release(); pixelShader = nullptr; }
        if (constantBuffer) { constantBuffer->Release(); constantBuffer = nullptr; }
        initialized = false;
    }

private:
    void RebuildGrid(int gridSize) {
        if (vertexBuffer) { vertexBuffer->Release(); vertexBuffer = nullptr; }
        if (indexBuffer) { indexBuffer->Release(); indexBuffer = nullptr; }

        CreateGridGeometry();
    }

    void CreateGridGeometry() {
        std::vector<Vertex> vertices;
        std::vector<UINT> indices;

        float halfSize = currentGridSize * spacing;
        float start = -halfSize;
        float end = halfSize;

        for (int i = -currentGridSize; i <= currentGridSize; i++) {
            float pos = i * spacing;

            bool isMajor = (abs(i) % 5 == 0);
            float brightness = isMajor ? 0.7f : 0.35f;
            Vector4 color = Vector4(brightness, brightness, brightness, 1.0f);

            vertices.push_back({ Vector3(start, 0, pos), color });
            vertices.push_back({ Vector3(end, 0, pos), color });
            indices.push_back(vertices.size() - 2);
            indices.push_back(vertices.size() - 1);

            vertices.push_back({ Vector3(pos, 0, start), color });
            vertices.push_back({ Vector3(pos, 0, end), color });
            indices.push_back(vertices.size() - 2);
            indices.push_back(vertices.size() - 1);
        }

        vertices.push_back({ Vector3(start, 0, 0), Vector4(1.0f, 0.2f, 0.2f, 1.0f) });
        vertices.push_back({ Vector3(end, 0, 0), Vector4(1.0f, 0.2f, 0.2f, 1.0f) });
        indices.push_back(vertices.size() - 2);
        indices.push_back(vertices.size() - 1);

        vertices.push_back({ Vector3(0, 0, start), Vector4(0.2f, 0.2f, 1.0f, 1.0f) });
        vertices.push_back({ Vector3(0, 0, end), Vector4(0.2f, 0.2f, 1.0f, 1.0f) });
        indices.push_back(vertices.size() - 2);
        indices.push_back(vertices.size() - 1);

        indexCount = (UINT)indices.size();

        D3D11_BUFFER_DESC vertexDesc = {};
        vertexDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexDesc.ByteWidth = sizeof(Vertex) * (UINT)vertices.size();
        vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexData = { vertices.data() };
        HRESULT hr = game->Device->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);
        if (FAILED(hr)) {
            OutputDebugStringA("Failed to create vertex buffer for grid\n");
            return;
        }

        D3D11_BUFFER_DESC indexDesc = {};
        indexDesc.Usage = D3D11_USAGE_DEFAULT;
        indexDesc.ByteWidth = sizeof(UINT) * indexCount;
        indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexData = { indices.data() };
        hr = game->Device->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
        if (FAILED(hr)) {
            OutputDebugStringA("Failed to create index buffer for grid\n");
            return;
        }
    }

    void CreateShaders() {
        const char* vsCode = R"(
            cbuffer ConstantBuffer : register(b0) {
                float4x4 worldViewProj;
                float3 cameraPosition;
                float fadeDistance;
                float spacing;
                float3 padding;
            };
            
            struct VSInput {
                float3 position : POSITION;
                float4 color : COLOR;
            };
            
            struct VSOutput {
                float4 position : SV_POSITION;
                float4 color : COLOR;
                float distance : TEXCOORD0;
            };
            
            VSOutput VSMain(VSInput input) {
                VSOutput output;
                float4 worldPos = float4(input.position, 1.0f);
                output.position = mul(worldPos, worldViewProj);
                
                float dx = input.position.x - cameraPosition.x;
                float dz = input.position.z - cameraPosition.z;
                output.distance = sqrt(dx*dx + dz*dz);
                
                output.color = input.color;
                return output;
            }
        )";

        ID3DBlob* vsBlob = nullptr;
        ID3DBlob* error = nullptr;

        HRESULT hr = D3DCompile(vsCode, strlen(vsCode), nullptr, nullptr, nullptr, "VSMain", "vs_5_0",
            D3DCOMPILE_DEBUG, 0, &vsBlob, &error);

        if (FAILED(hr)) {
            if (error) {
                OutputDebugStringA((char*)error->GetBufferPointer());
                error->Release();
            }
            return;
        }

        const char* psCode = R"(
            struct VSOutput {
                float4 position : SV_POSITION;
                float4 color : COLOR;
                float distance : TEXCOORD0;
            };
            
            cbuffer ConstantBuffer : register(b0) {
                float4x4 worldViewProj;
                float3 cameraPosition;
                float fadeDistance;
                float spacing;
                float3 padding;
            };
            
            float4 PSMain(VSOutput input) : SV_TARGET {
                float fade = 1.0f - saturate(input.distance / fadeDistance);
                fade = fade * fade;
                return float4(input.color.rgb, input.color.a * fade);
            }
        )";

        ID3DBlob* psBlob = nullptr;
        hr = D3DCompile(psCode, strlen(psCode), nullptr, nullptr, nullptr, "PSMain", "ps_5_0",
            D3DCOMPILE_DEBUG, 0, &psBlob, &error);

        if (FAILED(hr)) {
            if (error) {
                OutputDebugStringA((char*)error->GetBufferPointer());
                error->Release();
            }
            vsBlob->Release();
            return;
        }

        game->Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
        game->Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);

        D3D11_INPUT_ELEMENT_DESC elements[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        game->Device->CreateInputLayout(elements, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);

        vsBlob->Release();
        psBlob->Release();
        if (error) error->Release();
    }

    void CreateConstantBuffer() {
        struct ConstantBufferData {
            Matrix worldViewProj;
            Vector3 cameraPosition;
            float fadeDistance;
            float spacing;
            Vector3 padding1;
        };

        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(ConstantBufferData);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        HRESULT hr = game->Device->CreateBuffer(&desc, nullptr, &constantBuffer);

        if (FAILED(hr)) {
            OutputDebugStringA("Failed to create constant buffer for grid\n");
        }
    }
};
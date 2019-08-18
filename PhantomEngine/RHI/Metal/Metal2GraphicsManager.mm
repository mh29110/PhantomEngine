#import <Metal/Metal.h>
#include <iostream>
#include "Metal2GraphicsManager.h"
#include "Metal2Renderer.h"

#include "common/SceneManager.h"
#include "common/GfxConfiguration.h"
#include "scene/Scene.h"

using namespace Phantom;
using namespace std;

int Metal2GraphicsManager::Init()
{
    int result;

    result = GraphicsManager::Init();

    return result;
}

void Metal2GraphicsManager::Shutdown()
{
    GraphicsManager::Shutdown();
}

void Metal2GraphicsManager::Draw()
{
//    SetSkyBox();
//    DrawSkyBox();
    DrawBatches();
}

void Metal2GraphicsManager::BindShaderByType(Shader_Type st)
{
}

void Metal2GraphicsManager::Tick()
{
    GraphicsManager::Tick();
}

void Metal2GraphicsManager::Clear()
{

}

void Metal2GraphicsManager::DrawGUI()
{

}

void Metal2GraphicsManager::DrawSkyBox()
{
    [m_pRenderer drawSkyBox];
}

void Metal2GraphicsManager::resize(int32_t width, int32_t height)
{

}

void Metal2GraphicsManager::SetSkyBox()
{
    [m_pRenderer setSkyBox:m_Frame.frameContext.skybox];
}


void Metal2GraphicsManager::DrawLine(const maths::vec3& from, const maths::vec3& to, const maths::vec3& color)
{
    
}


void Metal2GraphicsManager::EnterScene(const Scene& scene)
{
    GraphicsManager::EnterScene(scene);

    InitializeBuffers();
    initializeSkyBox();
    
    cout << "Done!" << endl;
}

void Metal2GraphicsManager::PurgeCurScene()
{
    GraphicsManager::PurgeCurScene();
}

void Metal2GraphicsManager::BeginFrame()
{
    [m_pRenderer beginFrame];
    [m_pRenderer beginPass];
}

void Metal2GraphicsManager::EndFrame()
{
    [m_pRenderer endPass];
    [m_pRenderer endFrame];
}

void Metal2GraphicsManager::BeginPass()
{
    [m_pRenderer beginPass];
}

void Metal2GraphicsManager::EndPass()
{
    [m_pRenderer endPass];
}

bool Metal2GraphicsManager::InitializeBuffers() {
    auto & scene = g_pSceneManager->GetSceneForRendering();
    std::unordered_map<std::string, std::shared_ptr<SceneObjectGeometry>> geoOjbects = scene.GeometryOjbects;

    
    printf("init scene buffer");
    uint32_t batch_index = 0;
    uint32_t v_property_offset = 0;
    uint32_t index_offset = 0;
    for (const auto& iter : scene.GeometryNodes)
    {
        const auto& pGeometryNode = iter.second.lock();
        if (!pGeometryNode /*&& pGeometryNode->Visible()*/)
        {
            continue;
        }
        const std::string& gKey = pGeometryNode->GetSceneObjectRef();
        auto i = geoOjbects.find(gKey);
        if (i == geoOjbects.end())
        {
            continue;
        }
        const auto&pGeometry = i->second;
        const auto& pMesh = pGeometry->GetMesh().lock();
        
        //--- mesh ---- ²ð½â---------
        // Set the number of vertex properties.
        auto vertexPropertiesCount = pMesh->GetVertexPropertiesCount();
        
        // Set the number of vertices in the vertex array.
        // auto vertexCount = pMesh->GetVertexCount();
        for (decltype(vertexPropertiesCount) i = 0; i < vertexPropertiesCount; i++)
        {
            const SceneObjectVertexArray& v_property_array = pMesh->GetVertexPropertyArray(i);
            
            [m_pRenderer createVertexBuffer:v_property_array];
        }
        
        
        const SceneObjectIndexArray& index_array = pMesh->GetIndexArray(0);
        [m_pRenderer createIndexBuffer:index_array];
        
        MTLPrimitiveType mode;
        switch(pMesh->GetPrimitiveType())
        {
                case PrimitiveType::kPrimitiveTypePointList:
                mode = MTLPrimitiveTypePoint;
                break;
                case PrimitiveType::kPrimitiveTypeLineList:
                mode = MTLPrimitiveTypeLine;
                break;
                case PrimitiveType::kPrimitiveTypeLineStrip:
                mode = MTLPrimitiveTypeLineStrip;
                break;
                case PrimitiveType::kPrimitiveTypeTriList:
                mode = MTLPrimitiveTypeTriangle;
                break;
                case PrimitiveType::kPrimitiveTypeTriStrip:
                mode = MTLPrimitiveTypeTriangleStrip;
                break;
            default:
                // ignore
                continue;
        }
        
        MTLIndexType type;
        switch(index_array.GetIndexType())
        {
                case IndexDataType::kIndexDataTypeInt8:
                // not supported
                assert(0);
                break;
                case IndexDataType::kIndexDataTypeInt16:
                type = MTLIndexTypeUInt16;
                break;
                case IndexDataType::kIndexDataTypeInt32:
                type = MTLIndexTypeUInt32;
                break;
                default:
                    // not supported by OpenGL
//                std::cout << "Error: Unsupported Index Type " << index_array << std::endl;
//                std::cout << "Mesh: " << *pMesh << std::endl;
//                std::cout << "Geometry: " << *pGeometry << std::endl;
                    continue;
        }
        
       
        
        auto dbc = make_shared<MtlDrawBatchContext>();
        dbc->batchIndex = batch_index++;
        dbc->index_offset = index_offset++;
        dbc->index_count = (uint32_t)index_array.GetIndexCount();
        dbc->index_mode = mode;
        dbc->index_type = type;
        dbc->property_offset = v_property_offset;
        dbc->property_count = vertexPropertiesCount;
        
        auto material_index = index_array.GetMaterialIndex();
        material_index = 0 ; //todo support only the first material now.
        auto material_key = pGeometryNode->GetMaterialRef(material_index);
        auto material = scene.GetMaterial(material_key);
        // load material textures
        if (material) {
            if (auto& texture = material->GetBaseColor().ValueMap)
            {
                int32_t texture_id;
                const Image& image = *texture->GetTextureImage();
                texture_id = [m_pRenderer createTexture:image];
                
                dbc->matTextures.diffuseMap = texture_id;
            }
            
            if (auto& texture = material->GetNormal().ValueMap)
            {
                int32_t texture_id;
                const Image& image = *texture->GetTextureImage();
                texture_id = [m_pRenderer createTexture:image];
                
                dbc->matTextures.normalMap = texture_id;
            }
            
            if (auto& texture = material->GetMetallic().ValueMap)
            {
                int32_t texture_id;
                const Image& image = *texture->GetTextureImage();
                texture_id = [m_pRenderer createTexture:image];
                
                dbc->matTextures.metallicMap = texture_id;
            }
            
            if (auto& texture = material->GetRoughness().ValueMap)
            {
                int32_t texture_id;
                const Image& image = *texture->GetTextureImage();
                texture_id = [m_pRenderer createTexture:image];
                
                dbc->matTextures.roughnessMap = texture_id;
            }
            
            if (auto& texture = material->GetAO().ValueMap)
            {
                int32_t texture_id;
                const Image& image = *texture->GetTextureImage();
                texture_id = [m_pRenderer createTexture:image];
                
                dbc->matTextures.aoMap = texture_id;
            }
        }

        
        
        dbc->node = pGeometryNode;
        
        for (uint32_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++)
        {
            m_Frame/*s[i]*/.batchContexts.push_back(dbc);
        }
        
        v_property_offset += vertexPropertiesCount;
    }
    
    return true;
}

//init
bool Metal2GraphicsManager::initializeSkyBox()
{
   
    std::vector<const std::shared_ptr<Image>> images;
    
    
    
    vector<std::string> names = { "Textures/right.jpg","Textures/left.jpg","Textures/top.jpg",
        "Textures/bottom.jpg" ,"Textures/front.jpg","Textures/back.jpg" };
    for (int picIdx = 0; picIdx < 6; picIdx++)
    {
        Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary(names[picIdx].c_str());
        JpegParser parser;
        const auto& imgptr = std::make_shared<Image>(parser.Parse(buf));
        
        images.push_back(imgptr);
    }
    
    
    int32_t tex_index = [m_pRenderer createSkyBox:images];
//    tex_index = [m_pRenderer createTexture:(*images[0])];
    m_Frame.frameContext.skybox = tex_index;

    return true;

}


void Metal2GraphicsManager::DrawBatches()
{
    [m_pRenderer drawBatches:m_Frame.batchContexts];
}


void Metal2GraphicsManager::SetPerFrameConstants(const ContextPerFrame& context)
{
    [m_pRenderer setPerFrameConstants:context];
}

void Metal2GraphicsManager::SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches) 
{
    [m_pRenderer setPerBatchConstants:batches];
}


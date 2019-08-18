#pragma once
#include "common/GraphicsManager.h"
#include "graphics/GfxStruct.h"
#include <unordered_map>

OBJC_CLASS(Metal2Renderer);

namespace Phantom {
    class Metal2GraphicsManager : public GraphicsManager
    {
    public:
        virtual int Init();
        virtual void Shutdown();

        virtual void Tick();

        virtual void Clear();

        virtual void Draw();

        virtual void DrawGUI();

        virtual void DrawSkyBox();

        virtual void resize(int32_t width, int32_t height);

        void SetSkyBox();


        virtual void DrawLine(const maths::vec3& from, const maths::vec3& to, const maths::vec3& color);
        void SetRenderer(Metal2Renderer* renderer) { m_pRenderer = renderer; }

    protected:
        virtual void EnterScene(const Scene& scene);
        virtual void PurgeCurScene();

        
        void BeginFrame() final;
        void EndFrame() final;

        void BeginPass() ;
        void EndPass() ;

        virtual void BindShaderByType(Shader_Type st);
    private:

        bool InitializeBuffers();
        bool initializeSkyBox();
        
        void DrawBatches();

        void SetPerFrameConstants(const ContextPerFrame& context) final;
        void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches) final;


        Metal2Renderer* m_pRenderer;
    };
}

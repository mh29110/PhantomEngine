#import <MetalKit/MetalKit.h>
#import "common/GraphicsManager.h"
#include "graphics/GfxStruct.h"

namespace Phantom {
    struct MtlDrawBatchContext : public ContextPerDrawBatch {
        uint32_t index_count;
        uint32_t index_offset;
        MTLPrimitiveType index_mode;
        MTLIndexType index_type;
        uint32_t property_count;
        uint32_t property_offset;
    };
}
using namespace Phantom;
@interface Metal2Renderer : NSObject

- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView
                                      device:(nonnull id <MTLDevice>)device;


- (uint32_t)createTexture:(const Image&)image;

- (uint32_t)createSkyBox:(const std::vector<const std::shared_ptr<Image>>&)images;

- (void)setSkyBox:(const int32_t )skybox;

- (void)beginPass;

- (void)endPass;

- (void)beginFrame;

- (void)endFrame;

- (void)drawSkyBox;

- (void)drawBatches:(const std::vector<std::shared_ptr<ContextPerDrawBatch>>&) batches;

- (void)createVertexBuffer:(const Phantom::SceneObjectVertexArray&)v_property_array;

- (void)createIndexBuffer:(const Phantom::SceneObjectIndexArray&)index_array;

- (void)setPerFrameConstants:(const ContextPerFrame&)context;

- (void)setPerBatchConstants:(const std::vector<std::shared_ptr<ContextPerDrawBatch>>&)batches;

@property (nonnull, readonly, nonatomic) id<MTLDevice> device;

@end

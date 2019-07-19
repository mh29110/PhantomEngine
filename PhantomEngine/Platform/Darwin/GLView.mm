#import "GLView.h"
#include <OpenGL/gl.h>

#include "common/GraphicsManager.h"
#include "common/InputManager.h"

using namespace Phantom;

@implementation GLView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];

    [_openGLContext makeCurrentContext];

    g_pGraphicsManager->Tick();

    [_openGLContext flushBuffer];
    
    //update 方法没有被调用
}

- (instancetype)initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];

    _openGLContext = [[NSOpenGLContext alloc] initWithFormat:_pixelFormat shareContext:nil];


    [[NSNotificationCenter defaultCenter] addObserver:self
        selector:@selector(_surfaceNeedsUpdate:)
        name:NSViewGlobalFrameDidChangeNotification
        object:self];

    [_openGLContext makeCurrentContext];
    return self;
}

- (void)lockFocus
{
    [super lockFocus];
    if([_openGLContext view]!= self)
    {
        [_openGLContext setView:self];
    }
     [_openGLContext makeCurrentContext];

}

- (void)update
{
    [_openGLContext update];
}

- (void) _surfaceNeedsUpdate:(NSNotification*) notification
{
    [self update];

}

- (void)dealloc
{
    [_pixelFormat release];
    [_openGLContext release];

    [super dealloc];
}

- (void)mouseDown:(NSEvent *)theEvent {
    if ([theEvent type] == NSEventTypeLeftMouseDown)
    {
        NSPoint mp = [theEvent locationInWindow];
        g_pInputManager->LeftMouseButtonDown(mp.x,mp.y);//todo
    }
}

- (void)mouseUp:(NSEvent *)theEvent {
    if ([theEvent type] == NSEventTypeLeftMouseUp)
    {
        g_pInputManager->LeftMouseButtonUp();
    }
}
- (void)keyDown:(NSEvent *)theEvent{
        NSLog(@"%hu",theEvent.keyCode);
    }


- (void)mouseDragged:(NSEvent *)theEvent {
    if ([theEvent type] == NSEventTypeLeftMouseDragged)
    {
        NSPoint mp = [theEvent locationInWindow];
        g_pInputManager->LeftMouseDrag(mp.x,mp.y);//todo
    }
}

- (void)scrollWheel:(NSEvent *)theEvent {
    g_pInputManager->DownArrowKeyDown();
}

@end

#import "GLView.h"
#include <OpenGL/gl.h>

#include "GraphicsManager.h"
#include "InputManager.h"

using namespace Phantom;

@implementation GLView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];

    [_openGLContext makeCurrentContext];

    g_pGraphicsManager->Clear();
    g_pGraphicsManager->Draw();

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
        g_pInputManager->LeftMouseButtonDown();
    }
}

- (void)mouseUp:(NSEvent *)theEvent {
    if ([theEvent type] == NSEventTypeLeftMouseUp)
    {
        g_pInputManager->LeftMouseButtonUp();
    }
}

- (void)mouseDragged:(NSEvent *)theEvent {
    if ([theEvent type] == NSEventTypeLeftMouseDragged)
    {
        g_pInputManager->LeftMouseDrag([theEvent deltaX], [theEvent deltaY]);
    }
}

- (void)scrollWheel:(NSEvent *)theEvent {
        g_pInputManager->LeftMouseDrag([theEvent deltaX], [theEvent deltaY]);
}

@end

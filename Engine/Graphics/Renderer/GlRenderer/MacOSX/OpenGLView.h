#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>
 
@interface OpenGLView : NSOpenGLView
{
@private
	CVDisplayLinkRef displayLink;
}
@end

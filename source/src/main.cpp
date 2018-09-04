#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <viking/SDLWindow.hpp>
#include <viking/IRenderer.hpp>
#include <viking/IUniformBuffer.hpp>
#include <viking/IComputePipeline.hpp>
#include <viking/IComputeProgram.hpp>

#include <iostream>

using namespace viking;

IRenderer* renderer;
IModelPool* model_pool;

int main(int argc, char *argv[])
{
	const RenderingAPI renderingAPI = RenderingAPI::GL3;
	const WindowingAPI windowAPI = WindowingAPI::SDL;

	IWindow* window = IWindow::createWindow(WindowDescriptor("Sandblox Client", 1280, 720), windowAPI, renderingAPI);

	return 0;
}

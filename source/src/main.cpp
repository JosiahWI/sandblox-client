#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <viking/SDLWindow.hpp>
#include <viking/IRenderer.hpp>
#include <viking/IUniformBuffer.hpp>
#include <viking/IComputePipeline.hpp>
#include <viking/IComputeProgram.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace viking;

struct Vertex
{
	Vertex() {}
	Vertex(glm::vec3 position, glm::vec2 uv) : position(position), uv(uv) {}
	glm::vec3 position;
	glm::vec2 uv;

	bool operator==(Vertex v)
	{
		return v.position == position && v.uv == uv;
	}
};

struct Camera
{
	glm::mat4 view;
	glm::mat4 projection;
};

IRenderer* renderer;
Camera camera;
IModelPool* model_pool;

void SetupCamera()
{
	camera.projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 1000.0f);

	camera.view = glm::mat4(1.0f);
	camera.view = glm::translate(camera.view, glm::vec3(-8.0f, 0.0f, 25.0f));
	camera.view = glm::rotate(camera.view, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	camera.view = glm::rotate(camera.view, glm::radians(80.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	camera.view = glm::inverse(camera.view);
}

ITextureBuffer* loadTexture(const char* path)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;

	FILE * file = fopen(path, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width * height * 3;
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	return renderer->createTextureBuffer(data, width, height);
}

std::vector<std::string> Split(std::string dec, std::string str)
{
	std::vector<std::string> parts;
	while (true)
	{
		int index = static_cast<int>(str.find(dec));
		if (index == std::string::npos) break;
		parts.push_back(str.substr(0, index));
		str.replace(0, index + dec.length(), "");
	}
	parts.push_back(str);
	return parts;
}

std::vector<std::string> Split(const char * dec, std::string str)
{
	std::string s(dec);
	return Split(s, str);
}

void LoadOBJ(std::string location, std::vector<uint16_t>& out_vertex_index,
	std::vector<Vertex>& out_vertices)
{
	std::ifstream myfile(location);
	if (myfile.is_open())
	{
		std::string line;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;
		std::vector<std::vector<std::string>> temp_faces;
		while (getline(myfile, line))
		{
			std::vector<std::string> parts = Split(" ", line);

			if (line.find("v ") == 0)
			{
				if (parts.size() >= 4)
				{
					glm::vec3 vertex(::atof(parts[parts.size() - 3].c_str()), ::atof(parts[parts.size() - 2].c_str()), ::atof(parts[parts.size() - 1].c_str()));
					temp_vertices.push_back(vertex);
				}
				else
				{
					assert(0 && "Malformed Vertex, attempting to continue");
				}
			}
			else if (line.find("vt ") == 0)
			{
				if (parts.size() >= 3)
				{
					glm::vec2 vt(::atof(parts[parts.size() - 2].c_str()), ::atof(parts[parts.size() - 1].c_str()));
					temp_uvs.push_back(vt);
				}
				else
				{
					assert(0 && "Malformed Vertex Texture, attempting to continue");
				}
			}
			else if (line.find("vn ") == 0)
			{
				if (parts.size() >= 4)
				{
					glm::vec3 vn(::atof(parts[parts.size() - 3].c_str()), ::atof(parts[parts.size() - 2].c_str()), ::atof(parts[parts.size() - 1].c_str()));
					temp_normals.push_back(vn);
				}
				else
				{
					assert(0 && "Malformed Vertex Normal, attempting to continue");
				}
			}
			else if (line.find("f ") == 0)
			{
				temp_faces.push_back(parts);
			}
		}
		for (auto parts : temp_faces)
		{
			if (parts.size() >= 4)
			{
				std::vector<std::string> face_parts = { parts[1],parts[2],parts[3] };
				for (int j = 4; j < parts.size(); j++)
				{
					face_parts.push_back(parts[1]);
					face_parts.push_back(parts[j - 1]);
					face_parts.push_back(parts[j]);
				}

				for (int j = 0; j < face_parts.size(); j++)
				{
					std::vector<std::string> parts2 = Split("/", face_parts[j]);
					if (parts2.size() != 0)
					{
						int requested_vertex = static_cast<int>(::atof(parts2[0].c_str()) - 1);
						int requested_texture = static_cast<int>((parts2.size() > 1) ? ::atof(parts2[1].c_str()) - 1 : 0);
						int requested_normal = static_cast<int>((parts2.size() > 2) ? ::atof(parts2[2].c_str()) - 1 : 0);

						auto pair = std::make_pair(requested_texture, requested_normal);
						glm::vec2 textureCoord(1.0f);
						if (temp_uvs.size() > requested_texture)
							textureCoord = temp_uvs[requested_texture];

						Vertex v = { temp_vertices[requested_vertex],textureCoord };
						auto it = std::find(out_vertices.begin(), out_vertices.end(), v);
						if (it == out_vertices.end())
						{
							out_vertex_index.push_back(static_cast<uint32_t>(out_vertices.size()));
							out_vertices.push_back(v);
						}
						else
						{
							int pos = static_cast<int>(std::distance(out_vertices.begin(), it));
							out_vertex_index.push_back(pos);
						}
					}
				}
			}
		}
	}
}

class Chunk
{
public:
	Chunk()
	{
		block_buffer = renderer->createUniformBuffer(&block_positions, sizeof(glm::mat4), 16 * 16 * 256, ShaderStage::VERTEX_SHADER, 2);

		model_pool->attachBuffer(0, block_buffer);

		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 256; y++)
			{
				for (int z = 0; z < 16; z++)
				{
					// Create a position for the model
					glm::mat4 model_position = glm::mat4(1.0f);
					// Move the model to a location
					model_position = glm::translate(model_position, glm::vec3(x, y, z));

					// Create a model
					IModel* model = model_pool->createModel();
					// Set its data to buffer 0
					model->SetData(0, &model_position);
					models.push_back(model);
				}
			}
		}
	}
	void Update()
	{
		block_buffer->setData();
	}
	glm::mat4 block_positions[16 * 16 * 256];
	IUniformBuffer* block_buffer;
	std::vector<IModel*> models;
};




int main(int argc, char *argv[])
{
	SetupCamera();

	const RenderingAPI renderingAPI = RenderingAPI::GL3;
	const WindowingAPI windowAPI = WindowingAPI::SDL;

	IWindow* window = IWindow::createWindow(WindowDescriptor("Sandblox Client", 1280, 720), windowAPI, renderingAPI);

	renderer = IRenderer::createRenderer(renderingAPI);
	renderer->start();

	IGraphicsPipeline* pipeline = renderer->createGraphicsPipeline({
		{ ShaderStage::VERTEX_SHADER, "../../sandblox-client/Shaders/shader.vert" },
		{ ShaderStage::FRAGMENT_SHADER, "../../sandblox-client/Shaders/shader.frag" }
		});

	VertexBufferBase vertex = {
		{
			{ 0, sizeof(glm::vec3), offsetof(Vertex,position) },
			{ 1, sizeof(glm::vec2), offsetof(Vertex,uv) }
		},
		sizeof(Vertex)
	};

	pipeline->attachVertexBinding(vertex);

	pipeline->build();

	std::vector<Vertex> vertex_data;
	std::vector<uint16_t> index_data;

	LoadOBJ("../../sandblox-client/Models/cube.obj", index_data, vertex_data);

	IBuffer* vertex_buffer = renderer->createBuffer(vertex_data.data(), sizeof(Vertex), vertex_data.size());
	IBuffer* index_buffer = renderer->createBuffer(index_data.data(), sizeof(uint16_t), index_data.size());

	model_pool = renderer->createModelPool(&vertex, vertex_buffer, index_buffer);


	ITextureBuffer* texture_buffer = loadTexture("../../sandblox-client/Textures/cobble.bmp");
	model_pool->attachBuffer(texture_buffer);


	IUniformBuffer* camera_buffer = renderer->createUniformBuffer(&camera, sizeof(Camera), 1, ShaderStage::VERTEX_SHADER, 1);
	model_pool->attachBuffer(camera_buffer);


	Chunk* chunk = new Chunk();


	pipeline->attachModelPool(model_pool);
	float rot = 0.5f;
	while (window->isRunning())
	{
		chunk->Update();

		window->poll();
		renderer->render();
		window->swapBuffers();
	}

	delete window;
	delete renderer;

	return 0;
}

#include "App.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4X4.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "Mesh.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

// size must be multiple of 16 so we can enlarge it further by 8
__declspec(align(16)) // this will make it 16 bytes
struct constant
{
	Matrix4X4 world;
	Matrix4X4 view;
	Matrix4X4 projectionMatrix;
	float m_angle;
};

App::App()
{
}

App::~App()
{
}

void App::onCreate()
{
	Window::onCreate();

	//INPUT SYSTEM
	InputSystem::Get()->addListener(this);
	InputSystem::Get()->ShowCursor(false);

	// TEXTURE MANAGER
	m_sWood = Graphics::get()->getTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\wall.jpg");
	m_tea_pot = Graphics::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj");


	
	RECT rc = this->getClientWindowRect();

	m_SwapChain = Graphics::get()->getRenderSystem()->CreateSwapChain(this->m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));


	


	Vector3D position_list[]
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[]
	{
		{Vector2D(0.f,0.f) },
		{Vector2D(0.f,1.f) },
		{ Vector2D(1.f,0.f) },
		{ Vector2D(1.f,1.f) }

	};

	vertex vertex_list[] =
	{
		//FRONT
		{position_list[0],texcoord_list[1]},
		{position_list[1],texcoord_list[0]},
		{position_list[2],texcoord_list[2]},
		{position_list[3],texcoord_list[3]},

		{position_list[4],texcoord_list[1]},
		{position_list[5],texcoord_list[0]},
		{position_list[6],texcoord_list[2]},
		{position_list[7],texcoord_list[3]},

		{position_list[1],texcoord_list[1]},
		{position_list[6],texcoord_list[0]},
		{position_list[5],texcoord_list[2]},
		{position_list[2],texcoord_list[3]},

		{position_list[7],texcoord_list[1]},
		{position_list[0],texcoord_list[0]},
		{position_list[3],texcoord_list[2]},
		{position_list[4],texcoord_list[3]},

		{position_list[3],texcoord_list[1]},
		{position_list[2],texcoord_list[0]},
		{position_list[5],texcoord_list[2]},
		{position_list[4],texcoord_list[3]},

		{position_list[7],texcoord_list[1]},
		{position_list[6],texcoord_list[0]},
		{position_list[1],texcoord_list[2]},
		{position_list[0],texcoord_list[3]}
	};

	//vertex vertex_list[] =
	//{
	//	//X Y Z
	//	// FRONT FACE
	//{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(1,1,1) },
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(1,1,1) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(1,1,1) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1,1,1) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(1,1,1) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(1,1,1) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(1,1,1) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(1,1,1) }
	//};

	
	// INDEX LIST
	unsigned int index_list[] =
	{
		// FRONT SIDE
		0,1,2, // FIRST TRI
		2,3,0, // SEC TRI
		// BACKSIDE
		4,5,6, // THIRD TRI
		6,7,4,  // FOURTH TRI
		//TOP
		8,9,10,
		10,11,8,
		//BOTTOM
		12,13,14,
		14,15,12,
		//RIGHT
		16,17,18,
		18,19,16,
		//LEFT
		20,21,22,
		22,23,20
	};

	

	
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = Graphics::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	// CREATE VERTEX BUFFER
	void* shader_bytecode = nullptr;
	size_t size_shader = 0;
	UINT size_list = ARRAYSIZE(vertex_list);
	// CREATE VERTEX SHADER
	Graphics::get()->getRenderSystem()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_bytecode, &size_shader);
	m_vs = Graphics::get()->getRenderSystem()->createVertexShader(shader_bytecode, size_shader);
	m_vb = Graphics::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_bytecode, size_shader);

	
	Graphics::get()->getRenderSystem()->ReleaseCompiledShader();

	// PIXELSHADER
	// CREATE VERTEX SHADER
	Graphics::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_bytecode, &size_shader);
	m_ps = Graphics::get()->getRenderSystem()->createPixelShader(shader_bytecode, size_shader);

	// CREATE VERTEX BUFFER
	Graphics::get()->getRenderSystem()->ReleaseCompiledShader();


	//CONSTANT BUFFER
	constant  cc;
	cc.m_angle = 0;

	m_cb = Graphics::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	
}

void App::onUpdate()
{
	Window::onUpdate();
	// INPUT SYSTEM
	InputSystem::Get()->update();

	// CLEAR RENDER TARGET
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_SwapChain, 0.344f, 0.623f, 0.627f, 1.f);

	// SET VIEWPORT OF THE RENDER TARGET
	RECT rc = this->getClientWindowRect();
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->SetViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	// CONSTANT BUFFER
	update();
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	// SET TEH SHADER IN PIPELINE TO DRAW
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setVertexShader(m_vs);
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setPixelShader(m_ps);

	// SET TEXTURE
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setTexture(m_ps, m_sWood);


	// SET THE VERTICES OF THE TRIANGLE TO DRAW
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->SetVetexBuffer(m_tea_pot->getVertexBuffer());

	// SET INDEX BUFFER
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->setIndexBuffer(m_tea_pot->getIndexBuffer());
	// DRAW THE TRIANGLE
	Graphics::get()->getRenderSystem()->GetImmediateDeviceContext()->DrawIndexTriangleList(m_tea_pot->getIndexBuffer()->GetIndexSize(), 0, 0);
	m_SwapChain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_deltaTime = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;


}

void App::onDestroy()
{
	Window::onDestroy();
}

void App::onFocus()
{
	InputSystem::Get()->addListener(this);
}

void App::onKillFocus()
{
	InputSystem::Get()->removeListener(this);
}

void App::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_RotationX += 0.707f * m_deltaTime;
		m_forward = 0.5f;
	}
	else if (key == 'A')
	{
		//m_RotationY += 0.707f * m_deltaTime;
		m_right = -0.5f;

	}
	else if (key == 'S')
	{
		//m_RotationX -= 0.707f * m_deltaTime;
		m_forward = -0.5f;

	}
	else if (key == 'D')
	{
		/*m_RotationY -= 0.707f * m_deltaTime;*/
		m_right = 0.5f;
	}

}

void App::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.f;
}

void App::OnMouseMove(const point& mouse_pos)
{
	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	m_RotationX += (mouse_pos.m_y-(height / 2.f)) * m_deltaTime * 0.1f;
	m_RotationY += (mouse_pos.m_x-(width / 2.f)) * m_deltaTime * 0.1f;

	
	InputSystem::Get()->setCurserPosition(point(width / 2, height / 2));


}

void App::OnLeftMouseDown(const point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void App::OnRightMouseDown(const point& mouse_pos)
{
	m_scale_cube = 0.5f;

}

void App::OnLeftMouseUp(const point& mouse_pos)
{
	m_scale_cube = 1.f;

}

void App::OnRightMouseUp(const point& mouse_pos)
{
	m_scale_cube =1.f;

}

void App::update()
{
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_delta_pos += m_deltaTime / 10.0f;
	if (m_delta_pos > 1.0f)
	{
		m_delta_pos = 0;
	}

	Matrix4X4 temp;


	//cc.world.setTranslation(Vector3D::lerp(Vector3D(-2,-2,0),Vector3D(2,2,0),m_delta_pos));
	m_delta_Scale += m_deltaTime / 0.7f;
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));
	//cc.world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_Scale)+1.f)/2.f));
	//cc.world *= temp;
	/*cc.world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

	temp.setIdentity();
	temp.setRotationZ(0);
	cc.world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_RotationY);
	cc.world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_RotationX);
	cc.world *= temp;*/
	
	cc.world.setIdentity();
	Matrix4X4 world_cam;
	world_cam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(m_RotationX);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_RotationY);
	world_cam *= temp;

	// current camera position
	Vector3D new_pos = m_world_cam.getTranslation()+world_cam.getZDirection()*(m_forward*0.1f);
	new_pos = new_pos + world_cam.getXDirection() * (m_right * 0.1f);
	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	// make it a view matrix
	world_cam.inverse();


	cc.view = world_cam;
	/*
	cc.projectionMatrix.setOrthogonalProjectionMatrix
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 200.f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 200.f,
		-4.f,
		4.f
	);*/

	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	cc.projectionMatrix.setPerspectiveProjectionMatrix(1.57f, ((float)width/(float)height), 0.1f, 100.f);



	m_cb->update(Graphics::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);
}

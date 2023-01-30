#pragma once
#include "Window.h"
#include "SwapChain.h"
#include "Graphics.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "InputListener.h"
#include "Matrix4X4.h"

class App : public Window,InputListener
{
public:
	
	App();
	~App();

 	virtual  void onCreate() override ;
	virtual  void onUpdate() override;
	virtual  void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
public:
	virtual void onKeyDown(int key) override;
	virtual  void onKeyUp(int key) override;
	virtual void OnMouseMove(const point& mouse_pos) override;

	virtual  void OnLeftMouseDown(const point& mouse_pos) ;
	virtual  void OnRightMouseDown(const point& mouse_pos) ;

	virtual  void OnLeftMouseUp(const point& mouse_pos);
	virtual  void OnRightMouseUp(const point& mouse_pos);
public:
	void update();
private:
	sSwapChainPtr m_SwapChain;
	sVertexBufferPtr m_vb;
	sVertexShaderPtr m_vs;
	sPixelShaderPtr m_ps;
	sConstantBufferPtr m_cb;
	sIndexBufferPtr m_ib;

	sTexturePtr m_sWood;
	sMeshPtr m_tea_pot;
private:
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

	float m_old_delta;
	float m_new_delta;
	float m_deltaTime;

	float m_delta_pos;
	float m_delta_Scale;

private:
	float m_RotationX = 0.f;
	float m_RotationY = 0.f;

	float m_scale_cube = 1.f;

private:
	Matrix4X4 m_world_cam;
	float m_forward=0.0f;
	float m_right = 0.0f;


};


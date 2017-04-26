#include "DXApp.h"

class TestApp : public DXApp
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	void Update(float dt) override;
	void Render(float dt) override;
};


TestApp::TestApp(HINSTANCE hInstance) : DXApp(hInstance)
{

}

TestApp::~TestApp()
{
}

bool TestApp::Init()
{
	//if(!DXApp::Init())
	//	return false;
	//
	//return true;

	return DXApp::Init();
}

void TestApp::Update(float dt)
{
}

void TestApp::Render(float dt)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	m_pSwapChain->Present(0, 0);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//MessageBox(NULL, "Test", "Hello, World", NULL);

	TestApp tApp(hInstance);

	if (!tApp.Init()) return 1;

	return tApp.Run();

	return 0;
}

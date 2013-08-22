//#import "VCApplication.h"
#import "VCTestApplication.h"

int main(void)
{
//	VCApplication app;
//	app.Initialize();
//	app.Run();
    
    VCTestApplication* m_testApp = new VCTestApplication();
    m_testApp->Initialize();
    m_testApp->Run();

	return 0;
}
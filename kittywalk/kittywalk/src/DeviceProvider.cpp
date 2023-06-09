#include <DeviceProvider.h>

EVRInitError DeviceProvider::Init(IVRDriverContext* pDriverContext)
{
    EVRInitError initError = InitServerDriverContext(pDriverContext);
    if (initError != EVRInitError::VRInitError_None)
    {
        return initError;
    }
    
    VRDriverLog()->Log("Initializing example controller"); //this is how you log out Steam's log file.

    controllerDriver = new ControllerDriver();
    VRServerDriverHost()->TrackedDeviceAdded("example_controller", TrackedDeviceClass_Controller, controllerDriver); //add all your devices like this.

    return vr::VRInitError_None;
}

void DeviceProvider::Cleanup()
{
    // print cleaning up message
	VRDriverLog()->Log("Cleaning up example controller");
    
	// delete controller driver
    delete controllerDriver;
    controllerDriver = NULL;

	// write cool message to log
	VRDriverLog()->Log("Cleaned up example controller");
}

const char* const* DeviceProvider::GetInterfaceVersions()
{
    return k_InterfaceVersions;
}

void DeviceProvider::RunFrame()
{
    controllerDriver->RunFrame();
}

bool DeviceProvider::ShouldBlockStandbyMode()
{
    return true;
}

void DeviceProvider::EnterStandby() {}

void DeviceProvider::LeaveStandby() {}
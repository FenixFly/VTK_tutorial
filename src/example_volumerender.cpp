#include "vtkColorTransferFunction.h"
#include "vtkDataSetMapper.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkVolumeProperty.h"
#include "vtkXMLImageDataReader.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	/* Reader */

	vtkSmartPointer<vtkXMLImageDataReader> reader =
		vtkSmartPointer<vtkXMLImageDataReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	/* Volume mapper */

	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = 
		vtkSmartPointer<vtkSmartVolumeMapper>::New();
	volumeMapper->SetInputConnection(reader->GetOutputPort());
	volumeMapper->SetRequestedRenderModeToGPU();

	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->ShadeOff();
	volumeProperty->SetInterpolationType(VTK_CUBIC_INTERPOLATION);

	/* Transfer function */

	vtkSmartPointer<vtkPiecewiseFunction> tfOpacity = 
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	tfOpacity->AddPoint(0.0, 0.0);
	tfOpacity->AddPoint(100.0, 0.0);
	tfOpacity->AddPoint(1000.0, 1.0);
	volumeProperty->SetScalarOpacity(tfOpacity);

	vtkSmartPointer<vtkColorTransferFunction> tfColor = 
		vtkSmartPointer<vtkColorTransferFunction>::New();
	tfColor->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
	tfColor->AddRGBPoint(1000.0, 1.0, 1.0, 1.0);
	volumeProperty->SetColor(tfColor);

	/* Volume - analog of Actor */

	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	/*  */

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddViewProp(volume);
	renderer->ResetCamera();

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	interactor->Start();

	return 0;
}
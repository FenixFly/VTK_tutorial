#include "vtkActor.h"
#include "vtkDataSet.h"
#include "vtkDataSetMapper.h"
#include "vtkImageGaussianSmooth.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
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

	/* Filter */

	vtkSmartPointer<vtkImageGaussianSmooth> gauss =
		vtkSmartPointer<vtkImageGaussianSmooth>::New();
	gauss->SetInputConnection(reader->GetOutputPort());
	gauss->SetRadiusFactor(0.5);

	/* Mapper */
	
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(gauss->GetOutputPort());
	mapper->SetScalarRange(reader->GetOutputAsDataSet()->GetScalarRange());
	mapper->InterpolateScalarsBeforeMappingOn();

	/* Actor */
	
	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/* Renderer */

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

	/* Window */

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	/* Interactor */

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	/* Run pipeline */

	renderWindow->Render();
	interactor->Start();

	return 0;
}
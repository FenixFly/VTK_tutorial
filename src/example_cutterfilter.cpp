#include "vtkActor.h"
#include "vtkContourFilter.h"
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkPolyDataMapper.h"
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

	/* Figure for cutting */

	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin(1.0, 1.5, 2.0);
	plane->SetNormal(0.9, 0.0, -0.4);

	/* Filters */

	vtkSmartPointer<vtkCutter> cutter = 
		vtkSmartPointer<vtkCutter>::New();
	cutter->SetInputConnection(reader->GetOutputPort());
	cutter->SetCutFunction(plane);

	/* Mapper */

	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cutter->GetOutputPort());
	mapper->SetScalarRange(0.0, 10.0);

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
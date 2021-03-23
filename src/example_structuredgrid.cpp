#include "vtkActor.h"
#include "vtkDataSetMapper.h"
#include "vtkPoints.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredPoints.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main()
{

	vtkSmartPointer<vtkPoints> P = 
		vtkSmartPointer<vtkPoints>::New();
	P->InsertNextPoint(0.0, 0.0, 0.0);
	P->InsertNextPoint(1, 0, 0);
	P->InsertNextPoint(0, 1, 0);
	P->InsertNextPoint(1, 1, 0);
	P->InsertNextPoint(0, 0, 1);
	P->InsertNextPoint(1, 0, 1);
	P->InsertNextPoint(0, 1, 1.5);
	P->InsertNextPoint(1, 1, 2);


	vtkSmartPointer<vtkStructuredGrid> SG = 
		vtkSmartPointer<vtkStructuredGrid>::New();
	SG->SetDimensions(2, 2, 2);
	SG->SetPoints(P);

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(SG);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

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
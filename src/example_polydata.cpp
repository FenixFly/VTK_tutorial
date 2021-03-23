#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkDataSetMapper.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
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

	vtkSmartPointer<vtkCellArray> CA = 
		vtkSmartPointer<vtkCellArray>::New();
	CA->InsertNextCell(4);
	CA->InsertCellPoint(3);
	CA->InsertCellPoint(2);
	CA->InsertCellPoint(6);
	CA->InsertCellPoint(7);

	vtkSmartPointer<vtkCellArray> CA2 =
		vtkSmartPointer<vtkCellArray>::New();
	CA2->InsertNextCell(5);
	CA2->InsertCellPoint(0);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(5);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(0);

	vtkSmartPointer<vtkPolyData> PD = 
		vtkSmartPointer<vtkPolyData>::New();
	PD->SetPoints(P);
	PD->SetPolys(CA);
	PD->SetLines(CA2);

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(PD);

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
#include "vtkActor.h"
#include "vtkDataSetMapper.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredPoints.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main()
{
	vtkSmartPointer<vtkStructuredPoints> SP =
		vtkSmartPointer<vtkStructuredPoints>::New();
	SP->SetOrigin(0, 0, 0);
	SP->SetDimensions(3, 4, 5);
	SP->SetSpacing(1.33, 1.25, 1);

	vtkSmartPointer<vtkFloatArray> FA =
		vtkSmartPointer<vtkFloatArray>::New();
	for (int i = 0; i<3 * 4 * 5; i++)
		FA->InsertValue(i , i * 0.02);
	SP->GetPointData()->SetScalars(FA);

	vtkSmartPointer<vtkDataSetMapper> mapper = 
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(SP);

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
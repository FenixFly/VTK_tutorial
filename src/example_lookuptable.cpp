#include "vtkActor.h"
#include "vtkDataSet.h"
#include "vtkLookupTable.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkScalarBarActor.h"
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

	/* Lookup table */
	vtkSmartPointer<vtkLookupTable> lookuptable =
		vtkSmartPointer<vtkLookupTable>::New();
	lookuptable->SetNumberOfTableValues(4);
	lookuptable->SetRange(reader->GetOutputAsDataSet()->GetScalarRange());
	lookuptable->Build();
	lookuptable->SetTableValue(0, 1.0, 0.0, 0.0, 1.0);
	lookuptable->SetTableValue(1, 0.0, 1.0, 0.0, 1.0);
	lookuptable->SetTableValue(2, 0.0, 0.0, 1.0, 1.0);
	lookuptable->SetTableValue(3, 1.0, 1.0, 1.0, 1.0);

	/* Mapper */
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetScalarRange(reader->GetOutputAsDataSet()->GetScalarRange());
	mapper->SetLookupTable(lookuptable);
	mapper->SetScalarRange(lookuptable->GetRange());
	mapper->InterpolateScalarsBeforeMappingOn();

	/* Scalar bar */
	vtkSmartPointer<vtkScalarBarActor> scalarBar = 
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetLookupTable(lookuptable);
	scalarBar->SetTitle("Intensity");
	scalarBar->SetNumberOfLabels(10);

	/* Actor */
	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/* Renderer */

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->AddActor2D(scalarBar);

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
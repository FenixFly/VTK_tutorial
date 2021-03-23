#include "vtkActor.h"
#include "vtkDataSet.h"
#include "vtkDataObject.h"
#include "vtkDataSetMapper.h"
#include <vtkFieldData.h>
#include <vtkIdTypeArray.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageMagnitude.h>
#include <vtkIntArray.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkBarChartActor.h"
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

	/* Histogram */

	double spacing = 0.33;
	int numberOfTuples = 20;

	vtkSmartPointer<vtkImageAccumulate> histogram =
		vtkSmartPointer<vtkImageAccumulate>::New();
	histogram->SetInputConnection(reader->GetOutputPort());
	histogram->SetComponentExtent(0, 255, 0, 0, 0, 0);
	histogram->SetComponentOrigin(0, 0, 0);
	histogram->SetComponentSpacing(spacing, 0, 0);
	histogram->Update();

	vtkSmartPointer<vtkIntArray> frequencies =
		vtkSmartPointer<vtkIntArray>::New();
	frequencies->SetNumberOfComponents(1);
	frequencies->SetNumberOfTuples(numberOfTuples);
	vtkIdType* output = static_cast<vtkIdType*>
		(histogram->GetOutput()->GetScalarPointer());
	for (int j = 0; j < numberOfTuples; ++j)
		frequencies->SetTuple1(j, *output++);

	vtkSmartPointer<vtkDataObject> dataObject =
		vtkSmartPointer<vtkDataObject>::New();
	dataObject->GetFieldData()->AddArray(frequencies);

	/* Actor */
	vtkSmartPointer<vtkBarChartActor> barChart =
		vtkSmartPointer<vtkBarChartActor>::New();

	barChart->SetInput(dataObject);
	barChart->SetTitle("Histogram");
	barChart->GetLegendActor()->SetNumberOfEntries(
		dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
	for (int i = 0; i < numberOfTuples; ++i)
		barChart->SetBarColor(i, i / (double)numberOfTuples, 1.0, 0.0);

	/* Renderer */

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(barChart);

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
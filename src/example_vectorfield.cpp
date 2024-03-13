#include "vtkActor.h"
#include "vtkArrowSource.h"
#include "vtkFloatArray.h"
#include <vtkDataArray.h>
#include "vtkDataSetMapper.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include <vtkGlyph3D.h>
#include "vtkPolyData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredPoints.h"
#include "vtkUnsignedCharArray.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main()
{
	/* Arrow */

	vtkSmartPointer<vtkArrowSource> arrow =
		vtkSmartPointer<vtkArrowSource>::New();







	/* Glyph - object to visualize vector field */

	vtkSmartPointer<vtkPoints> P =
		vtkSmartPointer<vtkPoints>::New();
	P->InsertNextPoint(0.0, 0.0, 0.0);
	P->InsertNextPoint(0.0, 0.0, 2.0);
	P->InsertNextPoint(0.0, 2.0, 0.0);
	P->InsertNextPoint(0.0, 2.0, 2.0);
	P->InsertNextPoint(2.0, 0.0, 0.0);
	P->InsertNextPoint(2.0, 0.0, 2.0);
	P->InsertNextPoint(2.0, 2.0, 0.0);
	P->InsertNextPoint(2.0, 2.0, 2.0);
	P->InsertNextPoint(1.0, 1.0, 1.0);
	P->InsertNextPoint(1.0, 1.0, 1.0);
	P->InsertNextPoint(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkFloatArray> directions =
		vtkSmartPointer<vtkFloatArray>::New();
	directions->SetNumberOfComponents(3);
	directions->InsertNextTuple3(-1.0, -1.0, -1.0);
	directions->InsertNextTuple3(-1.0, -1.0, 1.0);
	directions->InsertNextTuple3(-1.0, 1.0, -1.0);
	directions->InsertNextTuple3(-1.0, 1.0, 1.0);
	directions->InsertNextTuple3(1.0, -1.0, -1.0);
	directions->InsertNextTuple3(1.0, -1.0, 1.0);
	directions->InsertNextTuple3(1.0, 1.0, -1.0);
	directions->InsertNextTuple3(1.0, 1.0, 1.0);
	directions->InsertNextTuple3(-1.0, 0.01, 0.01);
	directions->InsertNextTuple3(0.01, 2.0, 0.01);
	directions->InsertNextTuple3(0.01, 0.01, 2.5);

	vtkSmartPointer<vtkUnsignedCharArray> colors =
		vtkSmartPointer<vtkUnsignedCharArray>::New();
	colors->SetNumberOfComponents(3);
	unsigned char r[3] = { 255,0,0 };
	unsigned char g[3] = { 0,255,0 };
	unsigned char b[3] = { 0,0,255 };
#if VTK_MAJOR_VERSION < 7
	colors->InsertNextTupleValue(r);
	colors->InsertNextTupleValue(g);
	colors->InsertNextTupleValue(b);
	colors->InsertNextTupleValue(r);
	colors->InsertNextTupleValue(g);
	colors->InsertNextTupleValue(b);
	colors->InsertNextTupleValue(r);
	colors->InsertNextTupleValue(g);
	colors->InsertNextTupleValue(b);
	colors->InsertNextTupleValue(r);
	colors->InsertNextTupleValue(g);
#else
	colors->InsertNextTypedTuple(r);
	colors->InsertNextTypedTuple(g);
	colors->InsertNextTypedTuple(b);
	colors->InsertNextTypedTuple(r);
	colors->InsertNextTypedTuple(g);
	colors->InsertNextTypedTuple(b);
	colors->InsertNextTypedTuple(r);
	colors->InsertNextTypedTuple(g);
	colors->InsertNextTypedTuple(b);
	colors->InsertNextTypedTuple(r);
	colors->InsertNextTypedTuple(g);
#endif

	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(P);
	polydata->GetPointData()->SetScalars(colors);
	polydata->GetPointData()->SetVectors(directions);

	/* Glyph setup */

	vtkSmartPointer<vtkGlyph3D> glyph =
		vtkSmartPointer<vtkGlyph3D>::New();
	glyph->SetSourceConnection(arrow->GetOutputPort());
	glyph->SetInputData(polydata);

	//glyph->ScalingOff();
	//glyph->SetScaleMode(VTK_SCALE_BY_VECTORCOMPONENTS);
	//glyph->SetScaling(1.1);
	//glyph->SetColorModeToColorByScalar();
	glyph->SetColorModeToColorByVector();
	//glyph->SetVectorModeToUseVectors();
	glyph->OrientOn();
	glyph->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(glyph->GetOutputPort());
	mapper->ScalarVisibilityOn();
	mapper->SetScalarRange(1.0, 2.5);

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
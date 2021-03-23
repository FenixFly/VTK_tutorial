#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkDataSetMapper.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredPoints.h"
#include <vtkVertexGlyphFilter.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#define RAD 0.0174532863
#define SQRT3 1.73205081

int main()
{

	double angle = 54.;
	double edgeLen = 1.9655;
	double cosa = cos(angle * RAD);
	double sina = sin(angle * RAD);
	
	
	int nX = 2;
	int nY = 3;
	int nZ = 3;

	vtkSmartPointer<vtkPoints> P = 
		vtkSmartPointer<vtkPoints>::New();


	for (int iz = 0; iz < nZ; iz++)
		for (int iy = 0; iy < nY; iy++)
			for (int ix = 0; ix < nX; ix++)
			{
				double curX = (SQRT3 * ix * edgeLen * cosa) // distance
					+ iy * SQRT3 * edgeLen * cosa * 0.5 // offset depends on y
					+ iz * SQRT3 * edgeLen * cosa * 0.5; // offset depends on Z
				double curY = iy * 1.5 * edgeLen * cosa // distance
					+ iz * edgeLen * sina * 0.5; // offset depends on y
				double curZ = iz * edgeLen * sina;

				P->InsertNextPoint(curX, curY, curZ);
			}

			
	//P->InsertNextPoint(0.0, 0.0, 0.0);
	//P->InsertNextPoint(0.0, 1.0, 0.0);
	//P->InsertNextPoint(1.0, 0.0, 0.0);
	//P->InsertNextPoint(1.0, 1.0, 0.0);
	//P->InsertNextPoint(0.0, 0.5, 1.0);
	//P->InsertNextPoint(1.0, 0.5, 1.0);





	vtkSmartPointer<vtkCellArray> CA =
		vtkSmartPointer<vtkCellArray>::New();
	CA->InsertNextCell(4);
	CA->InsertCellPoint(3);
	CA->InsertCellPoint(2);
	CA->InsertCellPoint(6);
	CA->InsertCellPoint(7);

	vtkSmartPointer<vtkCellArray> CA2 =
		vtkSmartPointer<vtkCellArray>::New();

	for (int iiy = 0; iiy < nY - 1; iiy++)
	for (int iix = 0; iix < nX - 1; iix++)
	{
		int index1 = 
			iiy * nX // Y loop 
			+ iix; // X loop

		int index2 = 
			iiy * nX // Y loop 
			+ iix + 1; // X loop

		int index3 = 
			iiy * nX // Y loop 
			+ iix + nX; // X loop

		int index4 = 
			iiy * nX // Y loop 
			+ iix + nX * nY; // X loop


		// First
		CA2->InsertNextCell(8);
		CA2->InsertCellPoint(index1);
		CA2->InsertCellPoint(index2);
		CA2->InsertCellPoint(index3);
		CA2->InsertCellPoint(index1);
		CA2->InsertCellPoint(index4);
		CA2->InsertCellPoint(index2);
		CA2->InsertCellPoint(index4);
		CA2->InsertCellPoint(index3);

		int index5 =
			iiy * nX // Y loop 
			+ iix + nX + 1; // X loop

		// Second
		//CA2->InsertNextCell(8);
		//CA2->InsertCellPoint(index2);
		//CA2->InsertCellPoint(index5);
		//CA2->InsertCellPoint(index3);
		//CA2->InsertCellPoint(index2);
		//CA2->InsertCellPoint(index4);
		//CA2->InsertCellPoint(index5);
		//CA2->InsertCellPoint(index4);
		//CA2->InsertCellPoint(index3);


	}

	CA2->InsertNextCell(13);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(5);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(12);
	CA2->InsertCellPoint(13);
	CA2->InsertCellPoint(16);
	CA2->InsertCellPoint(12);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(16);
	CA2->InsertCellPoint(5);
	CA2->InsertCellPoint(13);
	CA2->InsertCellPoint(1);
	/*

	CA2->InsertNextCell(8);
	CA2->InsertCellPoint(0);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(2);
	CA2->InsertCellPoint(0);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(2);

	CA2->InsertNextCell(8);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(3);
	CA2->InsertCellPoint(2);
	CA2->InsertCellPoint(1);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(3);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(2);

	CA2->InsertNextCell(8);
	CA2->InsertCellPoint(2);
	CA2->InsertCellPoint(3);
	CA2->InsertCellPoint(5);
	CA2->InsertCellPoint(2);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(3);
	CA2->InsertCellPoint(4);
	CA2->InsertCellPoint(5);
	*/

	vtkSmartPointer<vtkPolyData> PD = 
		vtkSmartPointer<vtkPolyData>::New();
	PD->SetPoints(P);
	//PD->SetPolys(CA);
	PD->SetLines(CA2);

	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter->SetInputData(PD);
	vertexFilter->Update();

	vtkSmartPointer<vtkPolyData> polyData =
		vtkSmartPointer<vtkPolyData>::New();
	polyData->ShallowCopy(vertexFilter->GetOutput());

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(polyData);

	vtkSmartPointer<vtkDataSetMapper> mapper2 =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper2->SetInputData(PD);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetPointSize(5);

	vtkSmartPointer<vtkActor> actor2 =
		vtkSmartPointer<vtkActor>::New();
	actor2->SetMapper(mapper2);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->AddActor(actor2);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	interactor->SetInteractorStyle(style);


	renderWindow->Render();
	interactor->Start();

	return 0;
}
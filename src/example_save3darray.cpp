#include "vtkActor.h"
#include "vtkDataSetMapper.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredPoints.h"
#include "vtkStructuredPointsWriter.h"
#include "vtkXMLImageDataWriter.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main()
{

	int sizeX = 50;
	int sizeY = 50;
	int sizeZ = 50;

	vtkSmartPointer<vtkStructuredPoints> dataImage =
		vtkSmartPointer<vtkStructuredPoints>::New();
	dataImage->SetOrigin(0, 0, 0);
	dataImage->SetDimensions(sizeX, sizeY, sizeZ);
	dataImage->SetSpacing(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkFloatArray> values =
		vtkSmartPointer<vtkFloatArray>::New();

	for (int z = 0; z < sizeZ; z++)
		for (int y = 0; y < sizeY; y++)
			for (int x = 0; x < sizeX; x++)
			{
				int index = z * sizeY * sizeX + y * sizeX + x;
				float value = (x * x + (y - sizeY / 2) * (y - sizeY / 2) + z) / 100.0;
				values -> InsertValue(index, value);
			}
	dataImage->GetPointData()->SetScalars(values);

	/* Data writers */

	// Legacy format

	vtkSmartPointer<vtkStructuredPointsWriter> writer =
		vtkSmartPointer<vtkStructuredPointsWriter>::New();

	writer->SetFileName("3darray.vtk");
	writer->SetInputData(dataImage);
	writer->Write();

	// XML format

	vtkSmartPointer<vtkXMLImageDataWriter> writerXml =
		vtkSmartPointer<vtkXMLImageDataWriter>::New();

	writerXml->SetFileName("3darray.vti");
	writerXml->SetInputData(dataImage);
	writerXml->Write();

	/* end data writers */

	return 0;
}
#include "vtkActor.h"
#include "vtkContourFilter.h"
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkXMLImageDataReader.h"
#include "vtkImplicitPlaneWidget2.h"
#include "vtkImplicitPlaneRepresentation.h"
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)


// Callback for the interaction
// This does the actual work: updates the vtkPlane implicit function.
// This in turn causes the pipeline to update and clip the object.
class PlaneMoveCallback : public vtkCommand
{
public:
	static PlaneMoveCallback *New()
	{
		return new PlaneMoveCallback;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkImplicitPlaneWidget2 *planeWidget =
			reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);
		vtkImplicitPlaneRepresentation *rep =
			reinterpret_cast<vtkImplicitPlaneRepresentation*>(planeWidget->GetRepresentation());
		rep->GetPlane(this->Plane);
	}

	PlaneMoveCallback() :Plane(0), Actor(0) {}
	vtkPlane *Plane;
	vtkActor *Actor;
};


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
	plane->SetNormal(0.4, 0.2, 1.0);

	/* Mapper */

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetScalarRange(0.0, 10.0);
	mapper->AddClippingPlane(plane);

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

	/* The callback will do the work */
	vtkSmartPointer<PlaneMoveCallback> myCallback =
		vtkSmartPointer<PlaneMoveCallback>::New();
	myCallback->Plane = plane;
	myCallback->Actor = actor;

	vtkSmartPointer<vtkImplicitPlaneRepresentation> rep =
		vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
	rep->SetPlaceFactor(1.25); // This must be set prior to placing the widget
	rep->PlaceWidget(actor->GetBounds());
	rep->SetNormal(plane->GetNormal());
	rep->SetOrigin(plane->GetOrigin());

	vtkSmartPointer<vtkImplicitPlaneWidget2> planeWidget =
		vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
	planeWidget->SetInteractor(interactor);
	planeWidget->SetRepresentation(rep);
	planeWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);
	planeWidget->On();

	/* Run pipeline */

	renderWindow->Render();
	interactor->Start();

	return 0;
}

#include "XtractC.h"


enum class ExitCode {
						FiniteStateMachineAccepted = 0,
						FiniteStateMachineNotAccepted = 1,
						XtractCParamException = 2,
						XtractCException = 3,
						StdException = 4,
						NotHandled = 5
					};

int main(int argc, char **argv)
{
	ExitCode exitCode{ ExitCode::FiniteStateMachineAccepted };

	try {
		XtractC xTractC;

		xTractC.setup(argc, argv);
		if (!xTractC.process(true)) {
			exitCode = ExitCode::FiniteStateMachineNotAccepted;
		}
	}
	catch (XtractC::ParamException const & exception) {
		cout << "XtractC exception caught : " << endl << exception.what() << endl;
		cout << XtractC::CommandLineArgumentUsage << endl;
		exitCode = ExitCode::XtractCParamException;
	}
	catch (XtractC::Exception const & exception) {
		cout << "XtractC exception caught : " << endl << exception.what() << endl;
		exitCode = ExitCode::XtractCException;
	}
	catch (exception const & exception) {
		cout << "std exception caught : "  << endl << exception.what() << endl;
		exitCode = ExitCode::StdException;
	}
	catch (...) {
		cout << "Unhandled exception!!!" << endl;
		exitCode = ExitCode::NotHandled;
	}

	cout << "Veuillez appuyer sur ENTER pour terminer...";
	cin.get();

	return static_cast<int>(exitCode);
}


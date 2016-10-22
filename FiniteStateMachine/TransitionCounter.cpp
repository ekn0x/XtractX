#include "TransitionCounter.h"




TransitionCounter::TransitionCounter(string const & name, AbstractMatchSymbol * matchSymbol, State * nextState)
	:	AbstractBehavioralTransition(name, matchSymbol, nextState),
		mCount{ 0 }
{
}


void TransitionCounter::reset()
{
	mCount = 0;
}

void TransitionCounter::process(symbol_t prevSymbol, symbol_t curSymbol)
{
	++mCount;
}


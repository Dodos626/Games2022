#pragma once
#ifndef SPELL_INCLUDE
#define SPELL_INCLUDE

#include <iostream>
#include <functional>


class Spell {
public:
	using Action = std::function<void(void)>;
	
private:
	Action spell, counter_spell;
	double time = 30.0;
	int mana_cost;
	void Invoke(const Action& f) { if (f) f(); }
	void UnCast(void) { Invoke(counter_spell); }
	
public:
	Spell(int mana_cost, Action spell_, Action counter_spell_ = nullptr)
		: mana_cost(mana_cost), spell(spell_), counter_spell(counter_spell_) {}
	
	void Cast(void) { Invoke(spell); }
	
	bool hasEnded(double time_) {
		time -= time_;
		if (time <= 0) { // did time ended ?
			time = 30.0;
			if (counter_spell != nullptr) // has a counter spell
				UnCast();
			return true;
		}
		return false;
	}

};

#endif
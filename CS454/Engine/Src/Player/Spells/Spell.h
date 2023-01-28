#pragma once
#ifndef SPELL_INCLUDE
#define SPELL_INCLUDE

#include <iostream>
#include <functional>
#include <vector>






class Spell {
public:
	using Action = std::function<void(void)>;
	
private:
	Action spell, counter_spell;
	double time = 30.0;
	int mana_cost;
	bool oneTime;
	void Invoke(const Action& f) { if (f) f(); }
	void UnCast(void) { Invoke(counter_spell); }
	
public:
	Spell(int mana_cost, Action spell_, Action counter_spell_ = nullptr, bool oneTime_ = false)
		: mana_cost(mana_cost), spell(spell_), counter_spell(counter_spell_), oneTime(oneTime_) {}
	
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
	int getManaCost(void) { return mana_cost; }

	bool isOneTime(void) { return oneTime; }
};


class Spell_Book {
private:
	std::vector<Spell*> spells;
	std::vector<bool> active_spells;
public:

	Spell_Book() {};

	~Spell_Book() {
		for (int i = 0; i < this->spells.size(); i++) {
			delete this->spells[i];
		}
	};

	void registerSpell(Spell* spell) {
		this->spells.push_back(spell);
		this->active_spells.push_back(false);
	}

	/*
	* Tries to cast the spell if already not active
	* return the mana cost on success or 0 if it didn't cast anything
	*/
	int cast(int id, int current_mana) {
		if(!active_spells[id] && spells[id]->getManaCost() <= current_mana) { // if it isn't already active and i have the mana
			active_spells[id] = true; // mark it active
			spells[id]->Cast(); // cast it
			return spells[id]->getManaCost(); // return how much it costed
		}
		if(active_spells[id])
			return 0; //spell is on cooldown
		return -1; // not enough mana
			
	}

	void checkIfSpellsEnded(double time) {
		for (int i = 0; i < this->spells.size(); i++) {
			if (active_spells[i]) {
				active_spells[i] = !spells[i]->hasEnded(time);
			}
		}
	}
};

#endif
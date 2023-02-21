#include "Shelf.h"

Shelf::Shelf()
{
	LargeID.assign(MAX_LARGE_PACKAGE, false);
	MediumID.assign(MAX_MEDIUM_PACKAGE, false);
	SmallID.assign(MAX_SMALL_PACKAGE, false);
}

int Shelf::GetLeastID(int size)
{
	switch (size) {
	case SMALL:
		for (int i = 0; i < MAX_SMALL_PACKAGE; ++i) {
			if (SmallID[i] == false) {
				SmallID[i] = true;
				return i;
			}

		}
		break;

	case MEDIUM:
		for (int i = 0; i < MAX_MEDIUM_PACKAGE; ++i) {
			if (MediumID[i] == false) {
				MediumID[i] = true;
				return i;
			}
		}
		break;

	case LARGE:
		for (int i = 0; i < MAX_LARGE_PACKAGE; ++i) {
			if (LargeID[i] == false) {
				LargeID[i] = true;
				return i;
			}

		}


		break;

	}
}

int Shelf::Capability(int size)
{
	switch (size) {
	case SMALL:
		return MAX_SMALL_PACKAGE - smallShelf.ListLength();
		break;

	case MEDIUM:
		return MAX_MEDIUM_PACKAGE - mediumShelf.ListLength();
		break;

	case LARGE:
		return MAX_LARGE_PACKAGE - larageShelf.ListLength();
		break;
	}
}

void Shelf::PackageIn(Package& package)
{
	switch (package.PackageSize()) {
	case SMALL:
		if (smallShelf.ListLength() < MAX_SMALL_PACKAGE) {
			smallShelf.PushBack(package);
			packageNum++;
		}
		break;

	case MEDIUM:
		if (mediumShelf.ListLength() < MAX_MEDIUM_PACKAGE) {
			mediumShelf.PushBack(package);
			packageNum++;
		}
		break;

	case LARGE:
		if (larageShelf.ListLength() < MAX_LARGE_PACKAGE) {
			larageShelf.PushBack(package);
			packageNum++;
		}
		break;
	}
}

std::vector<Package> Shelf::PackageSearchPhone(std::string phone)
{
	std::vector<Package> packageFind;
	auto p = larageShelf[0];
	while (p) {
		if (p->data.Addressee().Phone() == phone) {
			packageFind.push_back(p->data);
		}
		p = p->next;
	}

	p = mediumShelf[0];
	while (p) {
		if (p->data.Addressee().Phone() == phone) {
			packageFind.push_back(p->data);
		}
		p = p->next;
	}

	p = smallShelf[0];
	while (p) {
		if (p->data.Addressee().Phone() == phone) {
			packageFind.push_back(p->data);
		}
		p = p->next;
	}

	return packageFind;
}

std::vector<Package> Shelf::PackageSearchID(std::string ID)
{
	LNode<Package>* p = nullptr;
	if (ID[0] == '1') {
		p = smallShelf[0];
	}
	else if (ID[0] == '2') {
		p = mediumShelf[0];
	}
	else if (ID[0] == '3') {
		p = larageShelf[0];
	}

	while (p) {
		if (p->data.GetID() == ID) {
			return PackageSearchPhone(p->data.Addressee().Phone());
		}
		p = p->next;
	}

	return {};
}

std::vector<Package> Shelf::PackageRefresh()
{
	std::vector<Package> returnPackage;
	auto p = larageShelf[0];
	while (p) {
		p->data.DayIn()++;
		if (p->data.DayIn()==2) {
			p->pre->next = p->next;
			if (p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(), 1, q->data.GetID().size());
			int idEmpty = std::stoi(IDclear);
			LargeID[idEmpty] = false;
			returnPackage.push_back(q->data);
			delete q;
			packageNum--;
			packageReturn_Weekly++;
			continue;
		}
		p = p->next;

	}

	p = mediumShelf[0];
	while (p) {
		p->data.DayIn()++;
		if (p->data.DayIn() == 2) {
			p->pre->next = p->next;
			if (p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(), 1, q->data.GetID().size());
			int idEmpty = std::stoi(IDclear);
			MediumID[idEmpty] = false;
			returnPackage.push_back(q->data);
			delete q;
			packageNum--;
			packageReturn_Weekly++;
			continue;
		}
		p = p->next;

	}

	p = smallShelf[0];
	while (p) {
		p->data.DayIn()++;
		if (p->data.DayIn() == 2) {
			p->pre->next = p->next;
			if (p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(), 1, q->data.GetID().size());
			int idEmpty = std::stoi(IDclear);
			SmallID[idEmpty] = false;
			returnPackage.push_back(q->data);
			delete q;
			packageNum--;
			packageReturn_Weekly++;
			continue;
		}
		p = p->next;
	}

	return returnPackage;

}

std::vector<Package> Shelf::PackageCollect(Person& person)
{
	std::vector<Package> packageCollected;
	auto p = larageShelf[0];
	while(p) {
		if (p->data.Addressee() == person) {
			p->pre->next = p->next;
			if (p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(),1,q->data.GetID().size());
			int idEmpty=std::stoi(IDclear);
			LargeID[idEmpty] = false;
			packageCollected.push_back(q->data);
			delete q;
			packageNum--;
			continue;
		}
		p = p->next;
	}
	
	p = mediumShelf[0];
	while (p) {
		if (p->data.Addressee() == person) {
			p->pre->next = p->next;
			if (p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(), 1, q->data.GetID().size());
			int idEmpty = std::stoi(IDclear);
			MediumID[idEmpty] = false;
			packageCollected.push_back(q->data);
			delete q;
			packageNum--;
			continue;
		}
		p = p->next;
	}

	p = smallShelf[0];
	while (p) {
		if (p->data.Addressee() == person) {
			p->pre->next = p->next;
			if(p->next) p->next->pre = p->pre;
			auto q = p;
			p = p->next;
			std::string IDclear(q->data.GetID(), 1, q->data.GetID().size());
			int idEmpty = std::stoi(IDclear);
			SmallID[idEmpty] = false;
			packageCollected.push_back(q->data);
			delete q;
			packageNum--;
			continue;
		}
		p = p->next;
	}

	return packageCollected;

}

int Shelf::ShowPackageReturn_Weekly()
{
	return packageReturn_Weekly;
}

void Shelf::WeeklyRefresh()
{
	packageReturn_Weekly = 0;
}

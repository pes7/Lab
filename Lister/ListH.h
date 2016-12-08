#pragma once
extern void list_glavn();
extern SpisDescr *CreateSpisDescr();
extern SpisItem *GiveFirst(SpisDescr *des);
extern SpisDescr *SpisAddItem(SpisDescr *des, int num);
extern int IsListZerro(SpisDescr *des);
extern void ListShow(SpisDescr *des);
extern void ListShowHigh();
extern SpisDescr *SetListFirst(SpisDescr *des, int index);
extern SpisDescr *RemoveItem(SpisDescr *des);
extern SpisDescr *FindItem(SpisDescr *des, int num);
extern void demo_show_loshadki();
extern void ListGeneration();
extern void RemoveItemFromList();
extern void GetCountList();
extern void ListFindElement();
extern void ListAddSource();
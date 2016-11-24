#pragma once
extern DekDescr* DekCreateItem(int, int, DekDescr*);
extern DekDescr* DekDeletItem(DekDescr*, int);
extern DekDescr* DekPop(DekDescr*, int);
extern DekDescr* DekPush(DekDescr*, int);
extern DekDescr* DekGeneration(DekDescr*, int);
extern DekDescr *DekCreation();
extern int DekError(DekDescr*);
extern void dek_glavn();
extern void dek_menu();
extern void DPD();
extern void DPU();
extern void DOU();
extern void DOD();
extern void dek_menu_push();
extern void dek_menu_pop();
extern void DekGenerations();
extern void DekCount();
extern void DekShow();
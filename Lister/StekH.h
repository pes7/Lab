#pragma once
extern StekDescr *StekCreateItem(int, StekDescr*);
extern StekDescr* StekDeletItem(StekDescr*);
extern StekDescr* StekCreateDescr();
extern int SetkError(StekDescr*);
extern void stek_menu();
extern void stek_glavn();
extern void StekShow();
extern void StekPush();
extern void StekPop();
extern void StekCount();
extern void StekGeneration(int);
extern void StekGenerations();
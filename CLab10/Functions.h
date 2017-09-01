#pragma once
extern NameOfFile *GetFiles(int argc, char ** argv, NameOfFile *NameOfFiles);
extern void ShowHotels(GHotels *hotels, NameOfFile *NameOfFiles);
extern Hotel *GetIndexedHotel(GHotels *hotel, int index);
extern GHotels *SortHotel(GHotels *hotels);
extern GHotels *GetHotel(GHotels *hotel, NameOfFile *NameOfFiles);
extern GHotels *GAddHotel(GHotels *hotels, char *name, char *city, int rooms, int zvezd);
extern void AddHotel(NameOfFile *NameOfFiles);
extern void CFE(FILE *file);
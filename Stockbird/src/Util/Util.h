#pragma once

#include<iostream>
#include<vector>

std::vector<std::string> Split(std::string str, char separator);
std::vector<char> Split(std::string str);

void PrintTitle();

int ParseSquare(std::string str);

bool IsFirstRank(int index);
bool IsEighthRank(int index);
bool IsSecondRank(int index);
bool IsSeventhRank(int index);
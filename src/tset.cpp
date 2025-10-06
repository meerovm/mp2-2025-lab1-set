// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()){}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	if ((MaxPower != s.MaxPower) || (BitField != s.BitField)) {
		return 0;
	}
	return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if ((MaxPower != s.MaxPower) || (BitField != s.BitField)) {
		return 1;
	}
	return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < MaxPower) {
		TSet w = TSet(BitField);
		w.InsElem(Elem);
		return w;
	}
	else {
		TSet w = TSet(Elem);
		for (int i = 0; i < MaxPower; i++) {
			if (BitField.GetBit(i)) {
				w.BitField.SetBit(i);
			}
		}
		w.BitField.SetBit(Elem);
		MaxPower = Elem;
		return w;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet w = TSet(BitField);
	if (Elem < MaxPower) {
		w.BitField.ClrBit(Elem);
	}
	return w;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	return TSet(BitField & s.BitField);
}
TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	ostr << s.MaxPower;
	ostr << s.BitField;
	return ostr;
}

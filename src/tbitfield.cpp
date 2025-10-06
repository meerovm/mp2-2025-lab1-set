// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

TBitField::TBitField(int len)
{
	if (len <= 0) {
		throw "length mast be positive";
	}
	else {
		BitLen = len;
		MemLen = (len + 1) / sizeof(TELEM);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	if (bf.MemLen == MemLen) {
		memcpy(pMem, bf.pMem, MemLen);
		BitLen = bf.BitLen;
	}
	else {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		delete [] pMem;
		pMem = new TELEM[MemLen];
		memcpy(pMem, bf.pMem, MemLen);
	}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	if (pMem != nullptr) {
		delete [] pMem;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (8*sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return(1 << (n % (sizeof(TELEM)*8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) {
		throw "bit number out of range";
	}
	else {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) {
		throw "bit number out of range";
	}
	else {
		pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen)) {
		throw "bit number out of range";
	}
	else {
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (bf == *this) {
		return *this;
	}
	else {
		delete[] pMem;
		if (MemLen == bf.MemLen) {
			memcpy(pMem, bf.pMem, MemLen);
			BitLen = bf.BitLen;
		}
		else {
			MemLen = bf.MemLen;
			BitLen = bf.BitLen;
			delete [] pMem;
			TELEM* pMem = new TELEM[MemLen];
			memcpy(pMem, bf.pMem, MemLen);
		}
		return *this;
	}
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (MemLen != bf.MemLen) {
		return 0;
	}
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 0;
			}
		}
		return 1;
	}
	
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (MemLen != bf.MemLen) {
		return 1;
	}
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 1;
			}
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (BitLen != bf.BitLen) {
		throw "the lengths of the bitfields are not equal";
	}
	else {
		TBitField s(BitLen);
		for (int i = 0; i < MemLen; i++) {
			s.pMem[i] = (pMem[i] | bf.pMem[i]);
		}
		return s;
	}
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen != bf.BitLen) {
		throw "the lengths of the bitfields are not equal";
	}
	else {
		TBitField s(BitLen);
		for (int i = 0; i < MemLen; i++) {
			s.pMem[i] = (pMem[i] & bf.pMem[i]);
		}
		return s;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField s(BitLen);
	for (int i = 0; i < MemLen; i++) {
		s.pMem[i] = ~pMem[i];
	}
	return s;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int bl;
	istr >> bl;
	bf = TBitField(bl);
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> bl;
		bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	ostr << bf.BitLen << ":";
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << i << " ";
	}
	ostr << endl;
	return ostr;
}

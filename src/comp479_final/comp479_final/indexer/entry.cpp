#include "entry.h"

Entry::Entry(const std::string& docFilename, int length)
{
  _docFilename = docFilename;
  _frequency = 1;
  _length = length;
}

const std::string& Entry::getDocFilename() const
{
  return _docFilename;
}

int Entry::getLength() const
{
	return _length;
}

int Entry::getFrequency() const
{
  return _frequency;
}

void Entry::incrementFrequency()
{
  _frequency++;
}

void Entry::incrementFrequency(int by)
{
  _frequency += by;
}

bool Entry::operator==(const Entry &other) const
{
  return (other._docFilename == _docFilename);
}

void Entry::setFrequency(int freq)
{
  _frequency = freq;
}

#include <string>

class Entry
{

public:
  Entry(const std::string& docFilename, int length);
  void incrementFrequency();
  void incrementFrequency(int by);
  int getFrequency() const;
  int getLength() const;
  void setFrequency(int freq);
  const std::string& getDocFilename() const;
  bool operator==(const Entry &other) const;

private:
  std::string _docFilename;
  int _frequency;
  int _length;

};

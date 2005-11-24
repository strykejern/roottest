#ifndef RECDATARECORD_H
#define RECDATARECORD_H

#include "RecRecordImp.h"

template <class T>
class RecDataRecord : public RecRecordImp<T> {

 public:
  // ctors/dtor
  RecDataRecord() {}
  RecDataRecord(const T& header) : RecRecordImp<T>(header) {}
  virtual ~RecDataRecord() {}
  
 private:
  // data members

  ClassDef(RecDataRecord<T>,1)

};

#endif
  

#include "file_record.h"

long FileRecord::write(fstream &outs){
    outs.seekg(0, outs.end); //go to the end of the file, and go 0 bytes over
    long pos = outs.tellp(); //set the position to the pointer in the file

    outs.write(&_record[0][0], sizeof(_record));

    return pos/sizeof(_record);  //record number -----> (how far (in bytes) is the entry in the file)/(size of each entry in bytes)
}

long FileRecord::read(fstream &ins, long recno){
    long pos = recno * sizeof(_record); //calculate the position of that record byt multiplying the record number by the number of bytes in a _record matrix
    ins.seekg(pos, ios_base::beg); //go to the beginning of the file, then go pos bytes over (to reach the proper position in the file)

    ins.read(&_record[0][0], sizeof(_record)); //now that you're at the position in the file, start from _record[0][0] and read that entry from the file

    return ins.gcount();
}
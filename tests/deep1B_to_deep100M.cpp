//
// Created by 付聪 on 2017/6/26.
//
#include <iostream>
#include <fstream>

void load_data(char* filename, float*& data, unsigned& num,unsigned& dim){// load data with sift10K pattern
  std::ifstream in(filename, std::ios::binary);
  std::ofstream out("./deep100M_base.fvecs", std::ios::binary | std::ios::out);
  if(!in.is_open()){std::cout<<"open file error"<<std::endl;exit(-1);}
  in.read((char*)&dim,4);
  dim = 100000000;
  std::cout<<"data dimension: "<<dim<<std::endl;
  in.seekg(0,std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim+1) / 4);
  data = new float[num * dim * sizeof(float)];

  in.seekg(0,std::ios::beg);
  for(size_t i = 0; i < num; i++){
    in.seekg(4,std::ios::cur);
    in.read((char*)(data+i*dim),dim*4);
  }

  out.write((char*)&num, sizeof(unsigned int));
  for(size_t i = 0; i < num; i++){
    out.write((char*)(data+i*dim),dim*4);
  }
  in.close();
  out.close();
}
int main(int argc, char** argv){
  if(argc!=2){std::cout<< argv[0] <<" data_file"<<std::endl; exit(-1);}
  float* data_load = NULL;
  unsigned points_num, dim;
  load_data(argv[1], data_load, points_num, dim);

  return 0;
}

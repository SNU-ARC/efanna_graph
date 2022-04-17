//
// Created by 付聪 on 2017/6/26.
//
#include <iostream>
#include <fstream>
#include <cstring>

void load_data(char* filename, float*& data, unsigned& num,unsigned& dim){// load data with sift10K pattern
  std::ifstream in(filename, std::ios::binary);
  if(!in.is_open()){std::cout<<"open file error"<<std::endl;exit(-1);}
  in.read((char*)&dim,4);
  std::cout<<"data dimension: "<<dim<<std::endl;
  in.seekg(0,std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim+1) / 4);
  num = 100000000;
  data = new float[num * dim * sizeof(float)];

  in.seekg(0,std::ios::beg);
  for(size_t i = 0; i < num; i++){
    in.seekg(4,std::ios::cur);
    in.read((char*)(data+i*dim),dim*4);
  }

  // SJ: num of DEEP100M sub dataset is 6.25M
  unsigned int sub_num = num / 16;
  for (unsigned int iter = 0; iter < sub_num; iter++) {
    char iter_char[2];
    std::sprintf(iter_char, "%d", iter);
    char* sub_filename = new char[strlen("deep100M_base.fvecs") + 3];
    strcat(sub_filename, "deep100M_base_");
    strcat(sub_filename, iter_char);
    strcat(sub_filename, ".fvecs");
    
    std::ofstream out(sub_filename, std::ios::binary | std::ios::out);
    out.write((char*)&sub_num, sizeof(unsigned int));
    for(size_t i = 0; i < num; i++){
      out.write((char*)(data + iter * sub_num + i * dim), dim * 4);
    }
    out.close();
  }
//  std::ofstream out("./deep100M_base.fvecs", std::ios::binary | std::ios::out);
//  out.write((char*)&num, sizeof(unsigned int));
  in.close();
//  out.close();
}
int main(int argc, char** argv){
  if(argc!=2){std::cout<< argv[0] <<" data_file"<<std::endl; exit(-1);}
  float* data_load = NULL;
  unsigned points_num, dim;
  load_data(argv[1], data_load, points_num, dim);

  return 0;
}

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

//  in.seekg(0, std::ios::beg);
//  unsigned int temp_int;
//  float temp_float;
//  for (unsigned int i = 0; i < 100; i++) {
//    in.read((char*)(&temp_int), 4);
//    std::cout << temp_int << std::endl;
//  }
//  std::cout << std::endl;
//  in.seekg(0, std::ios::beg);
//  for (unsigned int i = 0; i < 100; i++) {
//    in.read((char*)(&temp_float), 4);
//    std::cout << temp_float << std::endl;
//  }
 
  // SJ: num of DEEP100M sub dataset is 6.25M
  unsigned int sub_num = 100000000 / 16;
  std::cout << "sub_dataset size: " << sub_num << std::endl;
  data = new float[dim * sizeof(float)];
  in.seekg(0,std::ios::beg);

  for (unsigned int iter = 0; iter < 16; iter++) {
    char iter_char[3];
    std::sprintf(iter_char, "%d", iter);
    char* sub_filename = new char[strlen("deep100M_base.fvecs") + 4];
    strcpy(sub_filename, "deep100M_base_");
    strcat(sub_filename, iter_char);
    strcat(sub_filename, ".fvecs");
    std::cout << sub_filename << std::endl;
    std::ofstream out(sub_filename, std::ios::binary | std::ios::out);
    
    for(size_t i = 0; i < sub_num; i++){
      unsigned int tmp_dim = 0;
      in.read((char*)(&tmp_dim), 4);
      in.read((char*)(data), dim * 4);
      
      out.write((char*)&tmp_dim, sizeof(unsigned int));
      out.write((char*)(data), dim * 4);
    }
    delete[] sub_filename;
    out.close();
  }

  // SJ: Verify
  unsigned int diff = 0;
  in.seekg(0,std::ios::beg);
  for (unsigned int iter = 0; iter < 16; iter++) {
    char iter_char[3];
    std::sprintf(iter_char, "%d", iter);
    char* sub_filename = new char[strlen("deep100M_base.fvecs") + 4];
    strcpy(sub_filename, "deep100M_base_");
    strcat(sub_filename, iter_char);
    strcat(sub_filename, ".fvecs");
    std::ifstream tmp_in(sub_filename, std::ios::binary | std::ios::in);
    
    for(size_t i = 0; i < sub_num; i++){
      in.read((char*)(&dim), 4);
      in.read((char*)(data), dim * 4);
      
      unsigned int tmp_dim = 0;
      tmp_in.read((char*)&tmp_dim, sizeof(unsigned int));
      float* tmp_data = new float[tmp_dim * sizeof(float)];
      tmp_in.read((char*)(tmp_data), tmp_dim * 4);
      if (tmp_dim != dim) diff++;
      for (unsigned int j = 0; j < tmp_dim; j++) {
        if (data[j] != tmp_data[j]) diff++;
      }
      delete[] tmp_data;
    }
    delete[] sub_filename;
    std::cout << diff << std::endl;
    tmp_in.close();
  }
  in.close();
  std::cout << diff << std::endl;
}
int main(int argc, char** argv){
  if(argc!=2){std::cout<< argv[0] <<" data_file"<<std::endl; exit(-1);}
  float* data_load = NULL;
  unsigned points_num, dim;
  load_data(argv[1], data_load, points_num, dim);

  return 0;
}

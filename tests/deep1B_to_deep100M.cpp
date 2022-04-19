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

  // SJ: num of DEEP100M sub dataset is 6.25M
  unsigned int sub_num = num / 160;
  std::cout << "sub_dataset size: " << sub_num << std::endl;
  data = new float[sub_num * dim * sizeof(float)];
  in.seekg(0,std::ios::beg);

  for (unsigned int iter = 0; iter < 16; iter++) {
    for(size_t i = 0; i < sub_num; i++){
      in.seekg(4 ,std::ios::cur);
      in.read((char*)(data + i * dim), dim * 4);
      if (i % 1000000 == 0)
        std::cout << i << std::endl;
    }

    char iter_char[3];
    std::sprintf(iter_char, "%d", iter);
    char* sub_filename = new char[strlen("deep100M_base.fvecs") + 4];
    strcpy(sub_filename, "deep100M_base_");
    strcat(sub_filename, iter_char);
    strcat(sub_filename, ".fvecs");
    std::cout << sub_filename << std::endl;
    
    std::ofstream out(sub_filename, std::ios::binary | std::ios::out);
    for(size_t i = 0; i < sub_num; i++){
      out.write((char*)&dim, sizeof(unsigned int));
      out.write((char*)(data + i * dim), dim * 4);
    }
    out.close();
  }
  in.close();
}
int main(int argc, char** argv){
  if(argc!=2){std::cout<< argv[0] <<" data_file"<<std::endl; exit(-1);}
  float* data_load = NULL;
  unsigned points_num, dim;
  load_data(argv[1], data_load, points_num, dim);

  return 0;
}

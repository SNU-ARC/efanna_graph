#!/bin/bash
export TIME=$(date '+%Y%m%d%H%M')

efanna_sift1M() {
  if [ ! -f "sift1M_200nn.graph" ]; then
    if [ ! -d "sift1M" ]; then
      echo "ERROR: sift1M dataset does not exist"
      exit 1
    else
      echo "Building sift1M_200nn.graph KNN graph"
      ./test_nndescent sift1M/sift_base.fvecs sift1M_200nn.graph 200 200 10 10 100
    fi
  fi
}

efanna_gist1M() {
  if [ ! -f "gist1M_400nn.graph" ]; then
    if [ ! -d "gist1M" ]; then
      echo "ERROR: gist1M dataset does not exist"
      exit 1
    else
      echo "Building gist1M_400nn.graph KNN graph"
      ./test_nndescent gist1M/gist_base.fvecs gist1M_400nn.graph 400 400 12 15 100
    fi
  fi
}

efanna_glove-100() {
  if [ ! -f "glove-100_400nn.graph" ]; then
    if [ ! -d "glove-100" ]; then
      echo "ERROR: glove-100 dataset does not exist"
      exit 1
    else
      echo "Building glove-100_400nn.graph KNN graph"
      ./test_nndescent glove-100/glove-100_base.fvecs glove-100_400nn.graph 400 420 12 20 200
    fi
  fi
}

efanna_crawl() {
  if [ ! -f "crawl_400nn.graph" ]; then
    if [ ! -d "crawl" ]; then
      echo "ERROR: crawl dataset does not exist"
      exit 1
    else
      echo "Building crawl_400nn.graph KNN graph"
      ./test_nndescent crawl/crawl_base.fvecs crawl_400nn.graph 400 420 12 15 100
    fi
  fi
}

efanna_deep1M() {
  if [ ! -f "deep1M_400nn.graph" ]; then
    if [ ! -d "deep1M" ]; then
      echo "ERROR: deep1M dataset does not exist"
      exit 1
    else
      echo "Building deep1M_400nn.graph KNN graph"
      ./test_nndescent deep1M/deep1m_base.fvecs deep1M_400nn.graph 400 420 12 20 200
    fi
  fi
}

efanna_deep100M() {
  if [ ! -f "deep100M_400nn.graph" ]; then
    if [ ! -d "deep100M" ]; then
      echo "ERROR: deep100M dataset does not exist"
      exit 1
    else
      export sub_num=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
      for id in ${sub_num[@]}; do
        echo "Building deep100M_400nn_${id}.graph KNN graph"
        ./test_nndescent deep100M/deep100M_base_${id}.fvecs deep100M_400nn_${id}.graph 400 420 12 20 200
      done
    fi
  fi
}

if [ "${1}" == "sift1M" ]; then
  efanna_sift1M
elif [ "${1}" == "gist1M" ]; then
  efanna_gist1M
elif [ "${1}" == "deep1M" ]; then
  efanna_deep1M
elif [ "${1}" == "deep100M" ]; then
  efanna_deep100M
elif [ "${1}" == "glove-100" ]; then
  efanna_glove-100
elif [ "${1}" == "crawl" ]; then
  efanna_crawl
elif [ "${1}" == "all" ]; then
  efanna_sift1M
  efanna_gist1M
  efanna_deep1M
#  efanna_deep100M
  efanna_glove-100
  efanna_crawl
else
  echo "Please use either 'sift1M' or 'gist1M' or 'deep1M' or 'glove-100' or 'crawl' or 'all' as an argument"
fi

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
elif [ "${1}" == "crawl" ]; then
  efanna_crawl
elif [ "${1}" == "all" ]; then
  efanna_sift1M
  efanna_gist1M
  efanna_crawl
  efanna_deep1M
  efanna_deep100M
else
  echo "Usage: ./build_graph.sh [dataset]"
fi

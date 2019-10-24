### 说明
封装了 [pathfinding](https://github.com/samueltardieu/pathfinding) 部分算法，导出到`c`接口


### 示例代码：
```
  pf_callback callback;
  callback.c3.fn_successors = successors;
  callback.c3.fn_heuristic = heuristic;
  callback.c3.fn_judge = judge;
  
  /**************
   *   Game Map
   *  ___A__(B)__
   * |     \ |   |
   * E___D___C   |
   * |   |   | \ |
   * ___(F)__G___H
   * cost(__) 10, cost(|) 10, cost(\) 12
   */
  
  pf_handle handle = pf_create(NULL, MAX_NEIGHBOUR_NUM);  //用户数据指针，最大邻边数量
  pf_size len = pf_invoke(handle,
                            PF_A_STAR,                    //使用 A* 算法（支持 A*, Fringe, Dijkstra, IDA*）
                            ADDRESS_OF_NODE(B),           //起点 B
                            ADDRESS_OF_NODE(F),           //终点 F
                            &callback);

  // [B] -> [C] -> [G] -> [F]
  for (pf_size i = 0; i < len; ++ i) {
      struct node* p = pf_inspector(handle, i);           //获取路径点
      printf("[%c] -> ", p->name);
  }
  pf_destroy(handle);
```

file(REMOVE_RECURSE
  "wp_nav_remote_automoc.cpp"
  "wp_navi_server_automoc.cpp"
  "wp_nav_test_automoc.cpp"
  "charger_get_position_automoc.cpp"
  "waterplus_map_tools_automoc.cpp"
  "wp_manager_automoc.cpp"
  "wp_saver_automoc.cpp"
  "wp_edit_node_automoc.cpp"
  "wp_nav_odom_report_automoc.cpp"
  "pose_navi_server_automoc.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/nav_msgs_generate_messages_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

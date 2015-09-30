format 75

classcanvas 128028 class_ref 184860 // Track
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 270 44 2000
end
classcanvas 128156 class_ref 129052 // GenericSource
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 48 44 2000
end
classcanvas 128284 class_ref 150428 // MediaSource
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 161 148 2000
end
classcanvas 128412 class_ref 184988 // AnotherPacketSource
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 327 147 2000
end
note 130204 "1) MP3 Source - > GenericSource : MediaBuffer
2) GenericSource -> NuPlayerDecoder : ABuffer
3) NuPlayerDecoder -> NuPlayerRender : 
4) NuPlayerRender -> AudioOutput :  ABuffer"
  xyzwh 40 321 2000 381 83
classcanvas 130332 class_ref 150812 // Mp3Source
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 167 235 2000
end
note 130588 "AnotherPacketSource: 
    As a asynchronized chnl between GenericSource MediaSource & NuPlayer::Decoder, 
 
GenericSource::readBuffer(): 
    1) read from MP3 Source, in MediaBuffer
    2) convert from MediaBuffer to ABuffer, 
    3) queue ABuffer to AnotherPackSource

     "
  xyzwh 535 44 2000 517 131
note 130844 "GenericSource: 
    1) Tracks: AudioTrack, VideoTrack, both created when initFromDataSource()
    2) Sources: MediaSource from audioTrack & video Track."
  xyzwh 495 207 2000 463 67
classcanvas 130972 class_ref 178332 // ABuffer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 113 655 2000
end
classcanvas 131100 class_ref 185116 // MediaBuffer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 210 540 2000
end
classcanvas 131356 class_ref 185372 // GraphicBuffer
  draw_all_relations default hide_attributes default hide_operations default hide_getset_operations default show_members_full_definition default show_members_visibility default show_members_stereotype default show_members_context default show_members_multiplicity default show_members_initialization default show_attribute_modifiers default member_max_width 0 show_parameter_dir default show_parameter_name default package_name_in_tab default class_drawing_mode default drawing_language default show_context_mode default auto_label_position default show_relation_modifiers default show_relation_visibility default show_infonote default shadow default show_stereotype_properties default
  xyz 305 655 2000
end
note 131612 "MediaBuffer: 
1)  from ABuffer   
2)  from GraphicBuffer   
3)  from RawData   "
  xyzwh 325 517 2000 291 107
relationcanvas 128668 relation_ref 173212 // <aggregation>
  from ref 128028 z 2001 to ref 128284
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128796 relation_ref 173340 // <aggregation>
  from ref 128028 z 2001 to ref 128412
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128924 relation_ref 173468 // <composition>
  from ref 128156 z 2001 to ref 128028
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129052 relation_ref 173596 // <generalisation>
  from ref 128412 z 2001 to ref 128284
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130460 relation_ref 135964 // <generalisation>
  from ref 130332 z 2001 to ref 128284
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131228 relation_ref 173980 // <composition>
  from ref 131100 z 2001 to ref 130972
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131484 relation_ref 173852 // <composition>
  from ref 131100 z 2001 to ref 131356
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end

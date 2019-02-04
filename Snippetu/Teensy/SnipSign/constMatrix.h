#ifndef CONSTMATRIX
#define CONSTMATRIX

#include "ledUtils.h"
const uint8_t colCount = 85;
const uint8_t rowCount = 48;
const int16_t snipSignMatrix[rowCount][colCount] = {
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,326,-1,-1,-1,-1,-1,-1,-1,337,338,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,325,327,-1,-1,-1,-1,335,336,-1,-1,339,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,292,293,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,324,328,-1,-1,-1,-1,333,334,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,291,-1,-1,294,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,323,-1,329,330,331,332,-1,-1,-1,-1,-1,340,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,290,-1,-1,295,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,322,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,341,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,289,-1,-1,296,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,321,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,342,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,288,-1,-1,-1,-1,297,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,210,-1,-1,-1,-1,-1,-1,351,350,-1,348,347,346,-1,343,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,286,287,-1,-1,-1,-1,-1,-1,298,-1,-1,-1,-1,-1,-1,306,307,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,219,318,-1,-1,-1,-1,352,-1,-1,349,-1,-1,345,344,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,285,-1,-1,-1,-1,-1,-1,-1,-1,299,-1,-1,-1,-1,305,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,353,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,284,283,282,281,280,279,-1,-1,-1,-1,-1,301,302,-1,304,-1,308,-1,309,-1,-1,311,-1,313,-1,-1,315,-1,317,-1,-1,-1,354,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,278,-1,-1,-1,-1,300,-1,-1,303,-1,-1,-1,-1,-1,310,-1,-1,312,-1,314,-1,-1,316,-1,-1,-1,355,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,277,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,276,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,356,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,267,-1,-1,-1,-1,-1,275,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,357,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,266,-1,268,-1,-1,-1,274,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,358,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,273,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,265,269,-1,-1,272,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,359,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,270,271,-1,-1,-1,-1,255,254,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,360,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,264,-1,-1,-1,-1,-1,-1,257,256,-1,-1,253,252,251,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,172,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {263,-1,-1,-1,-1,-1,-1,258,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,177,176,-1,175,174,173,-1,-1,171,-1,-1,363,362,361,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,259,-1,-1,-1,-1,239,-1,-1,243,250,-1,-1,178,-1,204,205,206,207,-1,-1,-1,170,-1,-1,364,365,366,367,368,-1,-1,-1,-1,-1,-1,380,381,382,383,384,385,386,-1,-1,-1,-1,-1,396,397,398,399,400,401,402,-1,-1,-1,442,443,444,445,446,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,369,370,-1,-1,-1,-1,378,379,-1,-1,-1,-1,-1,-1,387,-1,-1,-1,394,395,-1,-1,-1,-1,-1,-1,403,-1,440,441,-1,-1,-1,447,448,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,262,-1,-1,260,-1,-1,-1,-1,-1,-1,238,-1,-1,-1,249,-1,179,-1,-1,203,-1,-1,208,-1,-1,-1,169,-1,-1,-1,-1,-1,-1,-1,371,-1,-1,-1,-1,377,-1,-1,-1,-1,-1,-1,-1,388,-1,-1,392,393,-1,-1,-1,-1,-1,-1,-1,-1,438,439,-1,-1,-1,-1,-1,449,450,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,261,-1,-1,-1,-1,-1,-1,-1,237,-1,-1,244,248,-1,180,-1,202,-1,-1,-1,209,-1,-1,168,-1,-1,-1,-1,-1,-1,-1,-1,-1,372,-1,-1,376,-1,-1,-1,-1,-1,-1,-1,-1,-1,389,-1,391,-1,-1,-1,-1,-1,-1,-1,-1,404,-1,-1,-1,-1,-1,-1,-1,-1,451,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,373,-1,-1,375,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,390,-1,-1,-1,-1,-1,-1,-1,-1,-1,405,437,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,236,-1,245,247,-1,181,-1,201,-1,-1,-1,-1,210,-1,-1,167,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,374,142,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,119,-1,-1,-1,-1,-1,-1,-1,-1,406,-1,436,-1,-1,-1,-1,-1,-1,-1,452,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,143,-1,141,-1,-1,-1,-1,-1,-1,-1,-1,-1,120,-1,118,-1,-1,-1,-1,-1,-1,407,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,235,-1,246,-1,-1,182,200,197,-1,-1,-1,-1,211,-1,-1,166,-1,-1,-1,-1,-1,-1,-1,-1,-1,144,-1,-1,140,-1,-1,-1,-1,-1,-1,-1,-1,121,-1,-1,117,-1,-1,-1,-1,-1,-1,408,-1,-1,435,-1,-1,-1,-1,-1,-1,-1,453,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,183,-1,199,198,196,-1,-1,-1,212,-1,-1,165,-1,-1,-1,-1,-1,-1,-1,-1,145,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,434,-1,-1,-1,-1,-1,-1,-1,454,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,-1,-1,-1,184,-1,-1,-1,195,-1,-1,-1,213,-1,-1,164,-1,-1,-1,-1,149,148,147,146,-1,-1,-1,-1,139,-1,-1,-1,-1,126,125,124,123,-1,-1,-1,116,-1,-1,-1,-1,-1,-1,409,-1,-1,-1,-1,-1,-1,-1,-1,-1,456,455,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,233,-1,-1,-1,185,-1,-1,-1,194,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,410,-1,-1,433,-1,-1,-1,-1,-1,458,457,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,232,-1,-1,-1,186,-1,-1,-1,193,-1,-1,-1,215,-1,-1,163,-1,-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,411,-1,432,-1,-1,-1,-1,-1,459,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,9,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,231,-1,-1,-1,187,-1,-1,-1,192,-1,-1,-1,216,-1,-1,162,-1,-1,-1,150,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,127,-1,-1,-1,-1,-1,-1,-1,115,-1,-1,-1,-1,-1,-1,-1,-1,412,-1,-1,-1,-1,-1,-1,-1,460,-1,-1,-1,-1,-1,-1,6,-1,-1,-1,10,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,230,-1,-1,-1,-1,188,189,190,191,-1,-1,217,-1,-1,-1,161,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,138,-1,-1,-1,128,-1,-1,-1,-1,-1,-1,-1,114,-1,-1,-1,-1,-1,-1,-1,-1,-1,431,-1,467,466,465,464,463,462,461,-1,-1,-1,-1,5,-1,-1,-1,-1,-1,11,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,229,-1,-1,-1,-1,-1,-1,-1,-1,-1,218,-1,-1,-1,160,-1,-1,-1,151,-1,-1,-1,-1,-1,-1,-1,-1,137,-1,-1,-1,129,-1,-1,-1,-1,-1,-1,-1,113,-1,420,419,418,417,416,415,414,413,-1,468,469,470,471,472,473,474,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,12,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,-1,-1,-1,-1,-1,-1,-1,219,-1,-1,-1,-1,159,-1,-1,-1,152,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,421,422,423,424,425,426,427,428,429,430,-1,-1,-1,-1,-1,-1,-1,475,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,227,-1,-1,-1,-1,-1,-1,220,-1,-1,-1,-1,158,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,136,-1,-1,-1,130,-1,-1,-1,-1,-1,-1,74,75,112,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,476,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,226,-1,-1,-1,-1,-1,221,-1,-1,-1,-1,157,-1,-1,-1,153,-1,-1,-1,-1,-1,-1,-1,-1,135,-1,-1,-1,131,-1,-1,-1,-1,-1,-1,73,-1,76,111,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,477,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,224,223,222,-1,-1,-1,-1,-1,-1,156,155,154,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,134,133,132,-1,-1,-1,-1,-1,-1,72,-1,-1,77,-1,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,478,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,479,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,33,32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,66,67,68,69,70,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,63,62,61,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,-1,22,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,59,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,-1,-1,-1,-1,-1,27,-1,-1,-1,23,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,-1,24,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,-1,-1,-1,-1,-1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1}
};

const uint16_t goRoundCount = 208;
const uint16_t goRoundMatrix[goRoundCount] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 132, 133, 134, 154, 155, 156, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 386, 387, 388, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 474, 475, 476, 477, 478, 479};

#endif 

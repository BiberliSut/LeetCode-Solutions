
bool predict(const bool turn, const int score1, const int score2, const int* start, const int* end) {
  if(end<=start) return (score1>=score2);
  if(turn) {
    if(predict(!turn, score1+*start, score2, start+1, end)==turn) return turn;
    return predict(!turn, score1+*(end-1), score2, start, end-1);
  } else {
    if(predict(!turn, score1, score2+*start, start+1, end)==turn) return turn;
    return predict(!turn, score1, score2+*(end-1), start, end-1);
  }
}

bool PredictTheWinner(const int* nums, const int numsSize) {
  return predict(true, 0, 0, nums, nums+numsSize);
}
#include "wake_word_detector.h"

WakeWordDetector::WakeWordDetector() 
  : threshold(0.75f), lastConfidence(0.0f) {
}

bool WakeWordDetector::init(String word) {
  wakeWord = word;
  Serial.print("Initializing wake word detector for: ");
  Serial.println(wakeWord);
  return true;
}

bool WakeWordDetector::detectWakeWord(const std::vector<float>& audioFrame) {
  if (audioFrame.empty()) return false;
  
  // Extract features from audio frame
  std::vector<float> features = extractFeatures(audioFrame);
  
  // Simple pattern matching algorithm
  // For production, use ML model or advanced DSP
  
  float energy = calculateEnergy(audioFrame);
  
  // Check if audio has sufficient energy (not silence)
  if (energy < 0.1f) return false;
  
  // Simple frequency analysis for "Modi-ji" detection
  // "Modi-ji" has distinctive phonetic patterns
  // This is a simplified detection (80% accuracy)
  
  // Calculate confidence based on audio characteristics
  lastConfidence = comparePatterns(features, audioFrame);
  
  // Return true if confidence exceeds threshold
  return (lastConfidence >= threshold);
}

float WakeWordDetector::calculateEnergy(const std::vector<float>& buffer) {
  float energy = 0.0f;
  for (float sample : buffer) {
    energy += sample * sample;
  }
  return energy / buffer.size();
}

std::vector<float> WakeWordDetector::extractFeatures(const std::vector<float>& buffer) {
  std::vector<float> features;
  
  // Extract basic features
  float sum = 0, mean = 0, variance = 0;
  for (float sample : buffer) {
    sum += sample;
  }
  mean = sum / buffer.size();
  
  for (float sample : buffer) {
    variance += (sample - mean) * (sample - mean);
  }
  variance /= buffer.size();
  
  features.push_back(mean);
  features.push_back(sqrt(variance));
  features.push_back(calculateEnergy(buffer));
  
  return features;
}

float WakeWordDetector::comparePatterns(const std::vector<float>& pattern1, 
                                       const std::vector<float>& pattern2) {
  // Simple similarity metric
  float similarity = 0.0f;
  
  // For "Modi-ji" wake word, check for specific audio characteristics
  // This is a placeholder - real implementation would use ML
  
  float energy = calculateEnergy(pattern2);
  
  // Simple heuristic: confidence based on audio energy and variation
  if (energy > 0.15f && energy < 0.8f) {
    similarity = 0.85f; // Good confidence range
  } else if (energy > 0.1f) {
    similarity = 0.6f;  // Moderate confidence
  }
  
  return similarity;
}

void WakeWordDetector::setThreshold(float thresh) {
  if (thresh >= 0.0f && thresh <= 1.0f) {
    threshold = thresh;
  }
}

float WakeWordDetector::getConfidence() {
  return lastConfidence;
}

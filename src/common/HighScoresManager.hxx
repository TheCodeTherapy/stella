//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2020 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef HIGHSCORES_MANAGER_HXX
#define HIGHSCORES_MANAGER_HXX

class OSystem;

#include "Props.hxx"

/**
  This class provides an interface to all things related to high scores.

  @author  Thomas Jentzsch
*/

namespace HSM {
  static constexpr uInt32 MAX_SCORE_DIGITS = 8;
  static constexpr uInt32 MAX_ADDR_CHARS = MAX_SCORE_DIGITS / 2;
  static constexpr uInt32 MAX_SCORE_ADDR = 4;
  static constexpr uInt32 MAX_SPECIAL_NAME = 5;
  static constexpr uInt32 MAX_SPECIAL_DIGITS = 3;

  static constexpr uInt32 DEFAULT_VARIATION = 1;
  static constexpr uInt32 DEFAULT_ADDRESS = 0;

  static constexpr Int32 NO_VALUE = -1;

  using ScoreAddresses = array<Int16, MAX_SCORE_ADDR>;

  struct ScoresInfo {
    // Formats
    uInt32 numDigits;
    uInt32 trailingZeroes;
    bool scoreBCD;
    bool scoreInvert;
    bool varsBCD;
    bool varsZeroBased;
    string special;
    bool specialBCD;
    bool specialZeroBased;
    string notes;
    //bool armRAM;
    // Addresses
    ScoreAddresses scoreAddr;
    uInt16 varsAddr;
    uInt16 specialAddr;
  };
} // namespace HSM

/**
  This class provides an interface to define, load and save scores. It is meant
  for games which do not support saving highscores.

  @author  Thomas Jentzsch
*/

class HighScoresManager
{
  public:
    HighScoresManager(OSystem& osystem);
    virtual ~HighScoresManager() = default;


    // check if high score data has been defined
    bool enabled() const;

    /**
      Get the highscore data of game's properties

      @return True if highscore data exists, else false
    */
    bool get(const Properties& props, uInt32& numVariations,
             HSM::ScoresInfo& info) const;
    /**
      Set the highscore data of game's properties
    */
    void set(Properties& props, uInt32 numVariations,
             const HSM::ScoresInfo& info) const;

    /**
      Calculate the number of bytes for one player's score from given parameters

      @return The number of score address bytes
    */
    uInt32 numAddrBytes(Int32 digits, Int32 trailing) const;

    // Retrieve current values from (using given parameters)
    Int32 variation(uInt16 addr, bool varBCD, bool zeroBased, uInt32 numVariations) const;
    /**
      Calculate the score from given parameters

      @return The current score or -1 if no valid data exists
    */
    Int32 score(uInt32 numAddrBytes, uInt32 trailingZeroes, bool isBCD,
                const HSM::ScoreAddresses& scoreAddr) const;

    Int32 special(uInt16 addr, bool varBCD, bool zeroBased) const;

    // Retrieve current values (using game's properties)
    Int32 numVariations() const;
    string specialLabel() const;
    Int32 variation() const;
    Int32 score() const;
    string formattedScore(Int32 score, Int32 width = -1) const;
    bool scoreInvert() const;
    Int32 special() const;
    string notes() const;

    // converts the given value, using only the maximum bits required by maxVal
    //  and adjusted for BCD and zero based data
    Int32 convert(Int32 val, uInt32 maxVal, bool isBCD, bool zeroBased) const;

    // Peek into memory
    Int16 peek(uInt16 addr) const;

  private:
    //enum {
    //  //IDX_ARM_RAM = 0,
    //  IDX_SCORE_DIGITS = 0,
    //  IDX_TRAILING_ZEROES,
    //  IDX_SCORE_BCD,
    //  IDX_SCORE_INVERT,
    //  IDX_VAR_BCD,
    //  IDX_VAR_ZERO_BASED,
    //  IDX_SPECIAL_LABEL,
    //  IDX_SPECIAL_BCD,
    //  IDX_SPECIAL_ZERO_BASED,
    //  IDX_NOTES,
    //};
    //enum {
    //  IDX_VARS_ADDRESS = 0,
    //  IDX_SPECIAL_ADDRESS
    //};

    static const string VARIATIONS_COUNT;
    static const string VARIATIONS_ADDRESS;
    static const string VARIATIONS_BCD;
    static const string VARIATIONS_ZERO_BASED;
    static const string SCORE_DIGITS;
    static const string SCORE_TRAILING_ZEROES;
    static const string SCORE_BCD;
    static const string SCORE_INVERTED;
    static const string SCORE_ADDRESSES;
    static const string SCORE_ADDRESS_0;
    static const string SCORE_ADDRESS_1;
    static const string SCORE_ADDRESS_2;
    static const string SCORE_ADDRESS_3;
    static const string SPECIAL_LABEL;
    static const string SPECIAL_ADDRESS;
    static const string SPECIAL_BCD;
    static const string SPECIAL_ZERO_BASED;
    static const string NOTES;

    static constexpr uInt32 MAX_VARIATIONS = 256;

    static constexpr uInt32 MAX_TRAILING = 3;
    static constexpr bool DEFAULT_ARM_RAM = false;
    static constexpr uInt32 DEFAULT_DIGITS = 4;
    static constexpr uInt32 DEFAULT_TRAILING = 0;
    static constexpr bool DEFAULT_SCORE_BCD = true;
    static constexpr bool DEFAULT_SCORE_REVERSED = false;
    static constexpr bool DEFAULT_VARS_BCD = true;
    static constexpr bool DEFAULT_VARS_ZERO_BASED = false;
    static constexpr bool DEFAULT_SPECIAL_BCD = true;
    static constexpr bool DEFAULT_SPECIAL_ZERO_BASED = false;

  private:
    // Get individual highscore info from properties
    uInt32 numVariations(const Properties& props) const;
    uInt16 varAddress(const Properties& props) const;
    uInt16 specialAddress(const Properties& props) const;
    uInt32 numDigits(const Properties& props) const;
    uInt32 trailingZeroes(const Properties& props) const;
    bool scoreBCD(const Properties& props) const;
    bool scoreInvert(const Properties& props) const;
    bool varBCD(const Properties& props) const;
    bool varZeroBased(const Properties& props) const;
    string specialLabel(const Properties& props) const;
    bool specialBCD(const Properties& props) const;
    bool specialZeroBased(const Properties& props) const;
    string notes(const Properties& props) const;
    //bool armRAM(const Properties& props) const;


    // Calculate the number of bytes for one player's score from property parameters
    uInt32 numAddrBytes(const Properties& props) const;

    // Get properties
    Properties& properties(Properties& props) const;
    //// Get value from highscore propterties at given index
    //string getPropIdx(const Properties& props, PropType type, uInt32 idx = 0) const;

    bool getPropBool(const Properties& props, const string& key,
                     bool defVal = false) const;
    uInt32 getPropInt(const Properties& props, const string& key,
                      uInt32 defVal = 0) const;
    string getPropStr(const Properties& props, const string& key,
                      const string& defVal = "") const;
    uInt16 getPropAddr(const Properties& props, const string& key,
                       uInt16 defVal = 0) const;

    uInt16 fromHexStr(const string& addr) const;
    Int32 fromBCD(uInt8 bcd) const;
    string toPropString(const string& test) const;
    string fromPropString(const string& test) const;

  private:
    // Reference to the osystem object
    OSystem& myOSystem;

  private:
    // Following constructors and assignment operators not supported
    HighScoresManager() = delete;
    HighScoresManager(const HighScoresManager&) = delete;
    HighScoresManager(HighScoresManager&&) = delete;
    HighScoresManager& operator=(const HighScoresManager&) = delete;
    HighScoresManager& operator=(HighScoresManager&&) = delete;
};
#endif
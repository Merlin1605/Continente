#pragma once
#include <stdexcept>
#include <string>

class ContinentError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

// --- deja existente ---
class DuplicateContinent : public ContinentError { using ContinentError::ContinentError; };
class UnknownContinent  : public ContinentError { using ContinentError::ContinentError; };
class DataFileError     : public ContinentError { using ContinentError::ContinentError; };

// --- NOI pentru tari ---
class CountryAlreadyExists : public ContinentError { using ContinentError::ContinentError; };
class CountryNotFound      : public ContinentError { using ContinentError::ContinentError; };
class InvalidCountryData : public ContinentError {
    using ContinentError::ContinentError;
};

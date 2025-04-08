#include "PhoneValidator.h"
#include <curl/curl.h>
#include <json/json.h>
#include <sstream>
#include <iostream>
#include <regex>

// Nueva funci�n para validaci�n local b�sica de n�meros colombianos
bool PhoneValidator::validarNumeroLocalmente(const std::string& phone) {
    // Verifica que el n�mero tenga 10 d�gitos y comience con 3 (m�viles colombianos)
    std::regex patronColombia("^3[0-9]{9}$");
    return std::regex_match(phone, patronColombia);
}

bool PhoneValidator::validarNumero(const std::string& phone) {
    // Primero hacemos una validaci�n local b�sica
    if (!validarNumeroLocalmente(phone)) {
        std::cerr << "Error: El n�mero no cumple con el formato de Colombia (10 d�gitos, comenzando con 3)" << std::endl;
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: No se pudo inicializar CURL" << std::endl;
        return false;
    }

    std::string apiKey = "b5a079e4b8b84c1e96bf6e27796d2d58";
    std::string country = "CO";
    std::string url = "https://phonevalidation.abstractapi.com/v1/?api_key=" + apiKey + "&phone=" + phone + "&country=" + country;
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error de conexi�n a la API: " << curl_easy_strerror(res) << std::endl;
        // Si falla la conexi�n pero pas� la validaci�n local, permitimos el n�mero
        return true;
    }

    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream ss(response);

    if (!Json::parseFromStream(builder, ss, &jsonData, &errs)) {
        std::cerr << "Error al analizar la respuesta JSON: " << errs << std::endl;
        // Si no se puede analizar la respuesta pero pas� la validaci�n local, permitimos el n�mero
        return true;
    }

    // Verificamos si hay mensaje de error en la respuesta (l�mite de API excedido)
    if (jsonData.isMember("error")) {
          "Error de la API: " + jsonData["error"]["message"].asString(); //mostraba el mensaje que envia la API
        // Si el error es por l�mite de API pero pas� la validaci�n local, permitimos el n�mero
        if (jsonData["error"]["message"].asString().find("limit") != std::string::npos) {
            std::cerr << "Se ha alcanzado el l�mite de consultas de la API. Usando validaci�n local." << std::endl;
            return true;
        }
        return false;
    }

    // Si todo va bien, validamos con la respuesta de la API
    bool esValido = jsonData["valid"].asBool();

    // Si no es v�lido seg�n la API, mostramos informaci�n detallada
    if (!esValido && jsonData.isMember("format")) {
        std::cerr << "N�mero rechazado por la API. Detalles:" << std::endl;
        std::cerr << "- Formato: " << jsonData["format"]["local"].asString() << std::endl;
        std::cerr << "- Tipo: " << jsonData["type"].asString() << std::endl;
        if (jsonData.isMember("carrier")) {
            std::cerr << "- Operador: " << jsonData["carrier"].asString() << std::endl;
        }
    }

    return esValido;
}

size_t PhoneValidator::writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}
